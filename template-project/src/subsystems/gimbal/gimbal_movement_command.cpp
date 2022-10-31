#include "gimbal_movement_command.hpp"

#include "tap/algorithms/math_user_utils.hpp"
#include "tap/errors/create_errors.hpp"

#include "controls/standard/control_interface.hpp"

namespace gimbal
{
GimbalMovementCommand::GimbalMovementCommand(GimbalSubsystem *const gimbal, src::Drivers *drivers) 
: gimbal(gimbal), drivers(drivers) 
{
     if (gimbal == nullptr)
    {
        return;
    }
    this->addSubsystemRequirement(dynamic_cast<tap::control::Subsystem *>(gimbal));
}
void  GimbalMovementCommand::initialize() {gimbal->controllerInput(0, 0);}

void  GimbalMovementCommand::execute()
{
    gimbal->controllerInput(drivers->control_interface.getGimbalYawInput(),
        drivers->control_interface.getGimbalPitchInput());
    //if(gimbal->motorOnline()) drivers->leds.set(drivers->leds.Blue, true);
    //else drivers->leds.set(drivers->leds.Red, true);
}

void  GimbalMovementCommand::end(bool) { gimbal->controllerInput(0, 0);}

bool  GimbalMovementCommand::isFinished() const { return false; }

}//namespace gimbal