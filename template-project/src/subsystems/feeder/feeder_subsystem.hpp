#ifndef FEEDER_SUBSYSTEM_HPP_
#define FEEDER_SUBSYSTEM_HPP_

#include "tap/control/subsystem.hpp"
#include "modm/math/filter/pid.hpp"
#include "tap/motor/dji_motor.hpp"
#include "tap/util_macros.hpp"
#include "controls/standard/standard_constants.hpp"
#include "drivers.hpp"

using namespace tap::algorithms;

namespace feeder{
class FeederSubsystem : public tap::control::Subsystem
{
public:
    FeederSubsystem(tap::Drivers *drivers)
    : tap::control::Subsystem(drivers), 
    feederMotor(drivers,
               tap::motor::MOTOR7,
               tap::can::CanBus::CAN_BUS2,
               false,
               "Yaw Motor"),
      targetRPM(0.0f),
      currentFeederMotorSpeed(0.0f)//,
      //feederPid(gimbalPid.YAW_GYRO_ABSOLUTE_PID_KP, gimbalPid.YAW_GYRO_ABSOLUTE_PID_KI, gimbalPid.YAW_GYRO_ABSOLUTE_PID_KD, 
      //gimbalPid.YAW_GYRO_ABSOLUTE_PID_MAX_IOUT, gimbalPid.YAW_GYRO_ABSOLUTE_PID_MAX_OUT),
      //feederSpeedPid(gimbalPid.YAW_SPEED_PID_KP, gimbalPid.YAW_SPEED_PID_KI, gimbalPid.YAW_SPEED_PID_KD,
      //gimbalPid.YAW_SPEED_PID_MAX_IOUT, gimbalPid.YAW_SPEED_PID_MAX_OUT)
      {}

    void initialize() override;
    void refresh() override;

    const char* getName() override {return "feeder subsystem";}

    void setFeederOutput(float output);

    // static inline float wrappedEncoderValueToRadians(int64_t encoderValue);

    void setTargetRPM(float angle) { targetRPM = angle; }

    float getFeederMotorRPM() const {return feederMotor.isMotorOnline() ? feederMotor.getShaftRPM() : 0.0f; }

    //value in degrees, Yaw = Pitch and Pitch = Roll cause taproot
    float getYaw() const {return drivers->bmi088.getPitch();}
    float getPitch() const {return drivers->bmi088.getRoll();}

    void updateFeederPid();

    void controllerInput(float RPMInput);
    void cvInput(float RPMInput);
    void noInputs();

    bool motorOnline(){ return feederMotor.isMotorOnline();
    }

private:
    tap::motor::DjiMotor feederMotor;

    //target RPM, idk the range of its value
    float targetRPM;

    //motor speed given in revolutions / min
    float currentFeederMotorSpeed;

    modm::Pid<float> feederPid;

    modm::Pid<float> feederSpeedPid;

    //current angles in radians
    float currentRPM;

    //desired error angles
    float feederError;

    //desired output speeds
    float feederSpeedOutput;

    //PID constancts
    //GIMBAL_PID gimbalPid;
    //Gimbal PID output to motor speed error factor
    //float motorSpeedFactor;

    bool inputsFound = false;
}; //class FeederSubsystem
}//namespace feeder


#endif