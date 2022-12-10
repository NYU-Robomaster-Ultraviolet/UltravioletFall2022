#include "ballistics_subsystem.hpp"
#include "modm/math/geometry/angle.hpp"

namespace ballistics{
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


}//namespace ballistics