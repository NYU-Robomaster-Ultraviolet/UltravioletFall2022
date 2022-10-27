#include "gimbal_subsystem.hpp"
#include "modm/math/geometry/angle.hpp"

namespace gimbal{
    //initilaizes the gimbal motors and make them not get any power
void GimbalSubsystem::initialize(){
    yawMotor.initialize();
    yawMotor.setDesiredOutput(0);
    pitchMotor.initialize();
    pitchMotor.setDesiredOutput(0);
}

void GimbalSubsystem::refresh(){ 
    if(!inputsFound) { //if there are no inputs, 
        if(yawMotor.isMotorOnline()) yawMotor.setDesiredOutput(0);
        if(pitchMotor.isMotorOnline()) pitchMotor.setDesiredOutput(0);
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
    if(-5 < yawError && yawError < 5){
        yawMotor.setDesiredOutput(0.0f);
    }
    else{
        yawPid.update(targetYaw - currentYaw);
        yawSpeedPid.update((yawPid.getValue() * MOTOR_SPEED_FACTOR) - currentYawMotorSpeed);
        yawSpeedOutput = limitVal<float>(yawSpeedPid.getValue(), -2000.0f, 2000.0f);
        if(-500.0f < yawSpeedOutput && yawSpeedOutput < 500.0f) yawSpeedOutput = 0.0f;
        yawMotor.setDesiredOutput(yawSpeedOutput);
        //drivers->leds.set(drivers->leds.Blue, false);
    }
}
void GimbalSubsystem::updatePitchPid(){
    //drivers->leds.set(drivers->leds.Blue, true);
    pitchError = targetPitch - currentPitch;
    if(-5 < pitchError && pitchError < 5){
        pitchPid.update(targetPitch - currentPitch);
    }
    else{
        pitchSpeedPid.update((pitchPid.getValue() * MOTOR_SPEED_FACTOR) - currentPitchMotorSpeed);
        pitchSpeedOutput = limitVal<float>(pitchSpeedPid.getValue(), -2000.0f, 2000.0f);
        if(-500.0f < pitchSpeedOutput && pitchSpeedOutput < 500.0f) pitchSpeedOutput = 0.0f;
        pitchMotor.setDesiredOutput(pitchSpeedOutput);
        //drivers->leds.set(drivers->leds.Blue, false);
    }
}
//this is the function that is called through the remote control input
void GimbalSubsystem::controllerInput(float yawInput, float pitchInput){
    setYawAngle(currentYaw + (yawInput * YAW_GIMBAL_SCALE));
    setPitchAngle(currentPitch + (pitchInput * PITCH_GIMBAL_SCALE));
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