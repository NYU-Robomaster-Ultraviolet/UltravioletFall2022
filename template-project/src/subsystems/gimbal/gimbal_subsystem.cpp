#include "gimbal_subsystem.hpp"
#include "modm/math/geometry/angle.hpp"

namespace gimbal{
    //initilaizes the gimbal motors and make them not get any power
void GimbalSubsystem::initialize(){
    yawMotor.initialize();
    yawMotor.setDesiredOutput(0);
    pitchMotor.initialize();
    pitchMotor.setDesiredOutput(0);
    uint16_t currentPitchEncoder = pitchMotor.getEncoderUnwrapped();
    startingPitch = wrappedEncoderValueToRadians(currentPitchEncoder);
}

void GimbalSubsystem::refresh(){ 
    if(!inputsFound) { //if there are no inputs, 
        if(yawMotor.isMotorOnline()) yawMotor.setDesiredOutput(0);
        if(pitchMotor.isMotorOnline()) pitchMotor.setDesiredOutput(stabalizePitch());
        noInputs();
    }
    else{
        inputsFound = false;
        if(yawMotor.isMotorOnline()){
            currentYawMotorSpeed = getYawMotorRPM(); //gets the rotational speed from motor
            uint16_t currentYawEncoder = yawMotor.getEncoderUnwrapped();
            currentYaw = wrappedEncoderValueToRadians(currentYawEncoder);
            updateYawPid();
        }
        if(pitchMotor.isMotorOnline()){
            currentPitchMotorSpeed = getPitchMotorRPM();
            uint16_t currentPitchEncoder = pitchMotor.getEncoderUnwrapped();
            currentPitch = wrappedEncoderValueToRadians(currentPitchEncoder);
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
    //drivers->leds.set(drivers->leds.Blue, true);
    yawError = targetYaw - currentYaw;
    if(-(constants.YAW_MINIMUM_RADS) < yawError && yawError < constants.YAW_MINIMUM_RADS){
        yawMotor.setDesiredOutput(0.0f);
    }
    else{
        yawPid.update(yawError);
        yawSpeedPid.update((yawPid.getValue() * constants.MOTOR_SPEED_FACTOR) - currentYawMotorSpeed);
        yawMotorOutput = limitVal<float>(yawSpeedPid.getValue(), constants.MIN_YAW_SPEED, constants.MAX_YAW_SPEED);
        yawMotor.setDesiredOutput(yawMotorOutput);
        //drivers->leds.set(drivers->leds.Blue, false);
    }
}
void GimbalSubsystem::updatePitchPid(){
    //drivers->leds.set(drivers->leds.Blue, true);
    pitchError = targetPitch - currentPitch;
    pitchPid.update(pitchError);
    if(-(constants.PITCH_MINIMUM_RADS) < pitchError && pitchError < constants.PITCH_MINIMUM_RADS){
        pitchMotorOutput = stabalizePitch();
    }
    else{
        pitchSpeedPid.update((pitchPid.getValue() * constants.MOTOR_SPEED_FACTOR) - currentPitchMotorSpeed);
        pitchMotorOutput = limitVal<float>(pitchSpeedPid.getValue(), -(constants.MIN_PITCH_SPEED), constants.MAX_PITCH_SPEED);
    }
    lastPitchMotorOutput = pitchMotorOutput;
    pitchMotor.setDesiredOutput(pitchMotorOutput);
        //drivers->leds.set(drivers->leds.Blue, false);
}
//this method will check if the motor is turning, and will return a new output to try to reach stable position
float GimbalSubsystem::stabalizePitch(){
    if(getPitchMotorRPM() > constants.MIN_PITCH_RPM) return lastPitchMotorOutput - constants.CURRENT_ADJUST;
    else if(getPitchMotorRPM() < -constants.MIN_PITCH_RPM) return lastPitchMotorOutput + constants.CURRENT_ADJUST;
    else return lastPitchMotorOutput; 
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
void GimbalSubsystem::noInputs(){setYawAngle(currentYaw), setPitchAngle(currentPitch);}
}//namespace gimbal