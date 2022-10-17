#include "chassis_movement_command.hpp"

#include "tap/algorithms/math_user_utils.hpp"
#include "tap/errors/create_errors.hpp"

#include "controls/standard/control_interface.hpp"

namespace chassis
{
ChassisMovementCommand::ChassisMovementCommand(
    ChassisSubsystem *const chassis,
    src::Drivers *drivers)
    : chassis(chassis),
      drivers(drivers)
{
    if (chassis == nullptr)
    {
        return;
    }
    this->addSubsystemRequirement(dynamic_cast<tap::control::Subsystem *>(chassis));
}

void  ChassisMovementCommand::initialize() {chassis->setDesiredOutput(0, 0, 0);}

void  ChassisMovementCommand::execute()
{
    chassis->setDesiredOutput(
        drivers->control_interface.getChassisXInput(),
        drivers->control_interface.getChassisYInput(),
        drivers->control_interface.getChassisRotationInput());
}

void  ChassisMovementCommand::end(bool) { chassis->setDesiredOutput(0, 0, 0); }

bool  ChassisMovementCommand::isFinished() const { return false; }
}  // namespace chassis