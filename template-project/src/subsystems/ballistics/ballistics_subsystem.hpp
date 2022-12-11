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
#include <vector>

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

    void initialize() override;//Shangyu
    //try to push it
  
    void refresh() override;//Srikar

    void handle_auto_aim();//Nirav
    void calc_pitch_yaw();//Nirav
    void make_angles(); //Lalit



private:
    //current gimbal pitch and yaw
    float startingPitch;
    float startingYaw;

    bool isTarget;
    bool autoaim;

    float barrelLength;
    float launchVelocity;

    float targetYaw;
    float targetPitch;

    vector<float> curr;
    vector<float> target;

    

}; //class GimbalSubsystem
}//namespace gimbal


#endif