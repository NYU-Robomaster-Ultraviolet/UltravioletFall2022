#include "gimbal_subsystem.hpp"
#include "modm/math/geometry/angle.hpp"

namespace gimbal{
    //initilaizes the gimbal motors and make them not get any power
void GimbalSubsystem::initialize(){
    pastTime = tap::arch::clock::getTimeMilliseconds();
    yawMotor.initialize();
    yawMotor.setDesiredOutput(0);
    pitchMotor.initialize();
    pitchMotor.setDesiredOutput(0);
    uint16_t currentPitchEncoder = pitchMotor.getEncoderUnwrapped();
    uint16_t currentYawEncoder = yawMotor.getEncoderUnwrapped();
    startingPitch = wrappedEncoderValueToRadians(currentPitchEncoder);
    startingYaw = wrappedEncoderValueToRadians(currentYawEncoder);
}

void GimbalSubsystem::refresh(){ 
    u_int32_t currentTime = tap::arch::clock::getTimeMilliseconds();
    timeError = currentTime - pastTime;
    pastTime = currentTime;
    if(inputsFound){
        if(yawMotor.isMotorOnline()){
            currentYawMotorSpeed = getYawMotorRPM(); //gets the rotational speed from motor
            uint16_t currentYawEncoder = yawMotor.getEncoderUnwrapped();
            currentYaw = wrappedEncoderValueToRadians(currentYawEncoder);
            updateYawPid();
        }
        if(pitchMotor.isMotorOnline()){
            currentPitchMotorSpeed = getPitchMotorRPM();
            uint16_t currentPitchEncoder = pitchMotor.getEncoderUnwrapped();
            currentPitch = wrappedEncoderValueToRadians(currentPitchEncoder) + constants.STARTING_PITCH;
            updatePitchPid();
        }
    }
}

//Takes in a encoded wrapped motor value and turns it into radians
inline float GimbalSubsystem::wrappedEncoderValueToRadians(int64_t encoderValue) {
    return (M_TWOPI * static_cast<float>(encoderValue)) / tap::motor::DjiMotor::ENC_RESOLUTION;
}

//this function will use the angel pid to determine the angel the robot will need to move to, then use a motor speed pid to change
//the motor speed accordingly
void GimbalSubsystem::updateYawPid(){
    yawError = (targetYaw - currentYaw) * constants.MOTOR_SPEED_FACTOR;
    if(-(constants.YAW_MINIMUM_RADS) < yawError && yawError < constants.YAW_MINIMUM_RADS){
        yawMotor.setDesiredOutput(0.0f);
    }
    else{
        yawMotorPid.runController(yawError, getYawMotorRPM(), timeError);
        yawMotorOutput = limitVal<float>(yawMotorPid.getOutput(), -constants.MAX_YAW_SPEED, constants.MAX_YAW_SPEED);
        if(-constants.MIN_YAW_SPEED < yawMotorOutput  && yawMotorOutput < constants.MIN_YAW_SPEED) yawMotorOutput = 0;
        yawMotor.setDesiredOutput(yawMotorOutput);
    }
}

//updates the pitch angle
void GimbalSubsystem::updatePitchPid(){
    pitchError = (targetPitch - currentPitch) * constants.MOTOR_SPEED_FACTOR;
    pitchMotorPid.runController(pitchError, getPitchMotorRPM(), timeError);
    if(-(constants.PITCH_MINIMUM_RADS) < pitchError && pitchError < constants.PITCH_MINIMUM_RADS){
        pitchMotorOutput = 0;
    }
    else{
        pitchMotorOutput = limitVal<float>(pitchMotorPid.getOutput(), -constants.MAX_PITCH_SPEED, constants.MAX_PITCH_SPEED);
    }
    pitchMotorOutput += gravityCompensation();
    if(-constants.MIN_PITCH_SPEED < pitchMotorOutput  && pitchMotorOutput < constants.MIN_PITCH_SPEED) pitchMotorOutput = 0;
    pitchMotor.setDesiredOutput(pitchMotorOutput);
}

//this method will check if the motor is turning, and will return a new output to try to reach stable position
float GimbalSubsystem::gravityCompensation(){
    float limitAngle = M_PI / 2;
    //greater than -20 degrees
    drivers->leds.set(drivers->leds.Blue, currentPitch > 1.5708);
    drivers->leds.set(drivers->leds.Red, currentPitch < 1.5708);
    if(currentPitch > 1.0472) limitAngle = limitVal<float>(currentPitch - constants.LEVEL_ANGLE, -M_PI, M_PI);
    return constants.GRAVITY_COMPENSATION_SCALAR * cosf(limitAngle);
}

//this is the function that is called through the remote control input
void GimbalSubsystem::controllerInput(float yawInput, float pitchInput){
    setYawAngle(currentYaw + (yawInput * constants.YAW_SCALE));
    setPitchAngle(currentPitch + (pitchInput * constants.PITCH_SCALE));
    inputsFound = true;
}

//this is the function that is called when CV team is sending offset angles through UART
void GimbalSubsystem::cvInput(float yawInput, float pitchInput){
    setYawAngle(yawInput);
    setPitchAngle(pitchInput);
    inputsFound = true;
}

void GimbalSubsystem::noInputs(){
    inputsFound = false;
    pitchMotor.setDesiredOutput(0);
    yawMotor.setDesiredOutput(0);
}
}//namespace gimbal