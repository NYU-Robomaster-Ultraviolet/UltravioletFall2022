#ifndef GIMBAL_SUBSYSTEM_HPP_
#define GIMBAL_SUBSYSTEM_HPP_

#include "tap/control/subsystem.hpp"
#include "modm/math/filter/pid.hpp"
#include "tap/motor/dji_motor.hpp"
#include "tap/util_macros.hpp"
#include "controls/standard/standard_constants.hpp"
#include "tap/util_macros.hpp"
#include "tap/algorithms/math_user_utils.hpp"
#include "drivers.hpp"
#include "tap/algorithms/smooth_pid.hpp"
#include "tap/architecture/clock.hpp"

using namespace tap::algorithms;

namespace gimbal{
class GimbalSubsystem : public tap::control::Subsystem
{
public:
    GimbalSubsystem(tap::Drivers *drivers)
    : tap::control::Subsystem(drivers), 
    yawMotor(drivers,
               tap::motor::MOTOR5,
               tap::can::CanBus::CAN_BUS2,
               false,
               "Yaw Motor"),
      pitchMotor(drivers,
                 tap::motor::MOTOR6,
                 tap::can::CanBus::CAN_BUS2,
                 false,
                 "Pitch Motor"),
      targetYaw(0.0f),
      targetPitch(0.0f),
      currentYawMotorSpeed(0.0f),
      currentPitchMotorSpeed(0.0f),
      yawMotorPid(YAW_PID),
      pitchMotorPid(PITCH_PID)
      {}

    void initialize() override;
    void refresh() override;

    const char* getName() override {return "gimbal subsystem";}

    void setYawOutput(float output);
    void setPitchOutput(float output);

    static inline float wrappedEncoderValueToRadians(int64_t encoderValue);

    void setYawAngle(float angle) { targetYaw = angle; }
    void setPitchAngle(float angle) {targetPitch = limitVal<float>(angle, constants.PITCH_MIN_ANGLE, 
        constants.PITCH_MAX_ANGLE - constants.STARTING_PITCH);}

    float getYawMotorRPM() const {return yawMotor.isMotorOnline() ? yawMotor.getShaftRPM() : 0.0f; }
    float getPitchMotorRPM() const {return pitchMotor.isMotorOnline() ? pitchMotor.getShaftRPM() : 0.0f; }

    //value in degrees, Yaw = Pitch and Pitch = Roll cause taproot
    float getYaw() const {return drivers->bmi088.getPitch();}
    float getPitch() const {return drivers->bmi088.getRoll();}

    //getters for motor speeds in rad/s, rpm * (pi / 120)
    float getYawVelocity() const {return (M_PI / 120) * yawMotor.getShaftRPM();}
    float getPitchVelocity() const {return (M_PI / 120) * pitchMotor.getShaftRPM();}

    //these methods will update both PID calculators and set motor speeds
    void updateYawPid();
    void updatePitchPid();

    //checks to see if motors are online or not
    bool yawOnline() const {return yawMotor.isMotorOnline();}
    bool pitchOnline() const {return pitchMotor.isMotorOnline();}

    /*these methods cover the three posibilities of gimbal position:
    either controller inputs, CV inputs, or no inputs*/
    void controllerInput(float yawInput, float pitchInput);
    void cvInput(float yawInput, float pitchInput);

    //this methods will take into consideration the current pitch of the gimbal and return a float value that will lock it in place
    float gravityCompensation();

private:
    tap::motor::DjiMotor yawMotor;
    tap::motor::DjiMotor pitchMotor;

    //starting angle
    float startingPitch;
    float startingYaw;
    //target angle, given in a value between -1 and 1
    float targetYaw;
    float targetPitch;
    //motor speed given in revolutions / min
    float currentYawMotorSpeed;
    float currentPitchMotorSpeed;

    //pid calculators that take in angular displacement and  angular velocity
    tap::algorithms::SmoothPid yawMotorPid;
    tap::algorithms::SmoothPid pitchMotorPid;

    //current angles in radians
    float currentYaw;
    float currentPitch;

    //desired error angles
    float yawError;
    float pitchError;

    //last time measurement
    u_int32_t pastTime = 0;
    //difference in time
    u_int32_t timeError = 0;

    //desired output values for motors in current
    float yawMotorOutput;
    float pitchMotorOutput;
    //all other gimbal constants
    GIMBAL_CONSTANTS constants;
    //Gimbal PID output to motor speed error factor
    float motorSpeedFactor;
    //checks if there are inputs or not
    bool inputsFound = false;
}; //class GimbalSubsystem
}//namespace gimbal


#endif