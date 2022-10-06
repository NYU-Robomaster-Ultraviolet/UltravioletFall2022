#ifndef GIMBAL_SUBSYSTEM_HPP_
#define GIMBAL_SUBSYSTEM_HPP_

#include "tap/control/subsystem.hpp"
#include "modm/math/filter/pid.hpp"
#include "tap/motor/dji_motor.hpp"
#include "tap/util_macros.hpp"
#include "controls/standard/standard_constants.hpp"
#include "tap/util_macros.hpp"
#include "tap/algorithms/math_user_utils.hpp"

using namespace tap::algorithms;

namespace gimbal{
class GimbalSubsystem : public tap::control::Subsystem
{
public:
    GimbalSubsystem(tap::Drivers* drivers);

    void initialize() override;
    void refresh() override;

    const char* getName() override {return "gimbal subsystem";}

    void setYawOutput(float output);
    void setPitchOutput(float output);

    void setYawAngle(float angle) { targetYaw = angle; }
    void setPitchAngel(float angle) {targetPitch = limitVal<float>(angle, -1.0f, 1.0f);}

    float getYawMotorRPM() const {yawMotor.isMotorOnline() ? yawMotor.getShaftRPM() : 0.0f; }
    float getPitchMotorRPM() const {pitchMotor.isMotorOnline() ? pitchMotor.getShaftRPM() : 0.0f; }

private:
    tap::motor::DjiMotor yawMotor;
    tap::motor::DjiMotor pitchMotor;

    //current angles in radians
    float currentYaw;
    float currentPitch;

    //angles to move to in radians 
    float targetYaw;
    float targetPitch;

    float desiredYawMotorOutput;
    float desiredPitchMotorOutput;

}; //class GimbalSubsystem


}//namespace gimbal


#endif