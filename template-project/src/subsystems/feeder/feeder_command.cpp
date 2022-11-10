#include "feeder_command.hpp"

#include "tap/algorithms/math_user_utils.hpp"
#include "tap/errors/create_errors.hpp"

#include "controls/standard/control_interface.hpp"

namespace feeder
{
FeederCommand::FeederCommand(
    FeederSubsystem *const feeder,
    src::Drivers *drivers)
    : drivers(drivers)
{
    if (chassis == nullptr)
    {
        return;
    }
    this->addSubsystemRequirement(dynamic_cast<tap::control::Subsystem *>(chassis));
}

void  FeederCommand::initialize() 
{
    //TODO: set to zero -> no pid movement
}

void  FeederCommand::execute()
{
    //TODO: set to max rpm
}

void  FeederCommand::end(bool) { //TODO }

bool  FeederCommand::isFinished() const { return false; }
}  // namespace feeder