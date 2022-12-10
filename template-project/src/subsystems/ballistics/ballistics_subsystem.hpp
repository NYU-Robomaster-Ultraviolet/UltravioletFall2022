#ifndef BALLISTICS_SUBSYSTEM_HPP_
#define BALLISTICS_SUBSYSTEM_HPP_

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
#include "controls/standard/imu_interface.hpp"

using namespace tap::algorithms;

namespace ballistics{
class BallisticsSubsystem : public tap::control::Subsystem
{
public:
    BallisticsSubsystem(src::Drivers *drivers)
    : tap::control::Subsystem(drivers), 
      targetYaw(0.0f),
      targetPitch(0.0f)
      {}


private:
    float startingPitch;
    float startingYaw;
    //target angle, given in a value between -1 and 1
    float targetYaw;
    float targetPitch;

    //current angles in radians
    float currentYaw;
    float currentPitch;

}; //class GimbalSubsystem
}//namespace gimbal


#endif