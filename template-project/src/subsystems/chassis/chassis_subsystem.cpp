#include "chassis_subsystem.hpp"

#include "tap/communication/serial/remote.hpp"
//#include "tap/algorithms/math_user_utils.hpp"

using namespace tap;

namespace chassis
{
void ChassisSubsystem::updateWheelvalues(){
    float FRRPM = frontRightMotor.getShaftRPM();
    float FLRPM = frontLeftMotor.getShaftRPM();
    float BRRPM = backRightMotor.getShaftRPM();
    float BLRPM = backLeftMotor.getShaftRPM();
    float FRPos = wrappedEncoderValueToRadians(frontRightMotor.getEncoderUnwrapped());
    float FLPos = wrappedEncoderValueToRadians(frontLeftMotor.getEncoderUnwrapped());
    float BRPos = wrappedEncoderValueToRadians(backRightMotor.getEncoderUnwrapped());
    float BLPos = wrappedEncoderValueToRadians(backLeftMotor.getEncoderUnwrapped());
    //format: name,RPM,EncoderPosition(rad);
    outputString = "FR," + std::to_string(FRRPM) + ',' +  std::to_string(FRPos) + ';' + 
    "FL," + std::to_string(FLRPM) + ',' +  std::to_string(FLPos) + ';' + 
    "BR," + std::to_string(BRRPM) + ',' +  std::to_string(BRPos) + ';' + 
    "BL," + std::to_string(BLRPM) + ',' +  std::to_string(BLPos) + ';' ;
}
void ChassisSubsystem::initialize()
{   
    frontLeftMotor.initialize();
    frontRightMotor.initialize();
    backLeftMotor.initialize();
    backRightMotor.initialize();
}
void ChassisSubsystem::refresh() {
    updateRpmPid(&frontLeftPid, &frontLeftMotor, frontLeftDesiredRpm);
    updateRpmPid(&frontRightPid, &frontRightMotor, frontRightDesiredRpm);
    updateRpmPid(&backLeftPid, &backLeftMotor, backLeftDesiredRpm);
    updateRpmPid(&backRightPid, &backRightMotor, backRightDesiredRpm);
}
void ChassisSubsystem::updateRpmPid(modm::Pid<float>* pid, tap::motor::DjiMotor* const motor, float desiredRpm) {
    pid->update(desiredRpm - motor->getShaftRPM());
    motor->setDesiredOutput(pid->getValue());
}

/*
    Give desired setpoints for chassis movement. +x is forward, +y is right, +r is clockwise (turning right). Expressed in body frame.
*/
void ChassisSubsystem::setDesiredOutput(float x, float y, float r) 
{
    // x, y, and r contained between -1 and 1
    //float centerDistance  = (powf(WHEELBASE_LENGTH / 2.0f, 2.0f)) + (powf(WHEELBASE_LENGTH / 2.0f, 2.0f));
    //float rotationRatio = modm::toRadian(centerDistance);
    //float rotationTranslated = modm::toDegree(r) / centerDistance;
    /*
    frontLeftDesiredRpm = tap::algorithms::limitVal<float>((x-y) * RPM_SCALE_FACTOR, -MAX_CURRENT_OUTPUT, MAX_CURRENT_OUTPUT);
    frontRightDesiredRpm = tap::algorithms::limitVal<float>((x+y) * RPM_SCALE_FACTOR, -MAX_CURRENT_OUTPUT, MAX_CURRENT_OUTPUT);
    backLeftDesiredRpm = tap::algorithms::limitVal<float>((x+y) * RPM_SCALE_FACTOR, -MAX_CURRENT_OUTPUT, MAX_CURRENT_OUTPUT);
    backRightDesiredRpm = tap::algorithms::limitVal<float>((x-y)* RPM_SCALE_FACTOR, -MAX_CURRENT_OUTPUT, MAX_CURRENT_OUTPUT);
    */
    
    frontLeftDesiredRpm = tap::algorithms::limitVal<float>(
        (RPM_SCALE_FACTOR * (-x+y+r)), -MAX_CURRENT_OUTPUT, MAX_CURRENT_OUTPUT);
    frontRightDesiredRpm = tap::algorithms::limitVal<float>(
        (RPM_SCALE_FACTOR* (x+y-r)), -MAX_CURRENT_OUTPUT, MAX_CURRENT_OUTPUT);
    backLeftDesiredRpm = tap::algorithms::limitVal<float>(
        (RPM_SCALE_FACTOR* (x+y+r)), -MAX_CURRENT_OUTPUT, MAX_CURRENT_OUTPUT);
    backRightDesiredRpm = tap::algorithms::limitVal<float>(
        (RPM_SCALE_FACTOR* (-x+y-r)), -MAX_CURRENT_OUTPUT, MAX_CURRENT_OUTPUT);
}
} //namespace chassis