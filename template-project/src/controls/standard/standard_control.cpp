#ifdef TARGET_STANDARD
#include "drivers.hpp"
#include "drivers_singleton.hpp"

#include "tap/control/command_mapper.hpp"
#include "tap/control/hold_command_mapping.hpp"
#include "tap/control/hold_repeat_command_mapping.hpp"
#include "tap/control/press_command_mapping.hpp"
#include "tap/control/setpoint/commands/calibrate_command.hpp"
#include "tap/control/toggle_command_mapping.hpp"

#include "subsystems/chassis/chassis_subsystem.hpp"

#include "subsystems/chassis/chassis_movement_command.hpp"

src::driversFunc drivers = src::DoNotUse_getDrivers;

using namespace tap;
using namespace tap::control;
using namespace tap::communication::serial;
using namespace chassis;

namespace StandardControl{
// Define subsystems here ------------------------------------------------
ChassisSubsystem chassis(drivers());
// Robot Specific Controllers ------------------------------------------------

// Define commands here ---------------------------------------------------
ChassisMovementCommand chassisMovementCommand(&chassis, drivers());
// Define command mappings here -------------------------------------------

// Register subsystems here -----------------------------------------------
void registerSubsystems(src::Drivers *drivers){
    drivers->commandScheduler.registerSubsystem(&chassis);
}
// Initialize subsystems here ---------------------------------------------
void initializeSubsystems() {
    chassis.initialize();
}
// Set default command here -----------------------------------------------
void setDefaultCommands(src::Drivers* drivers) {
    
}
// Set Commands scheduled on startup
void startupCommands(src::Drivers* drivers) {

}
// Register IO mappings here -----------------------------------------------
void registerIOMappings(src::Drivers* drivers) {
    
}
}//namespace standardControl


// Initialize subsystems ---------------------------------------------------
namespace src::Control
{
    void initializeSubsystemCommands(src::Drivers* drivers)
    {
        StandardControl::initializeSubsystems();
        StandardControl::registerSubsystems(drivers);
        StandardControl::setDefaultCommands(drivers);
        StandardControl::startupCommands(drivers);
        StandardControl::registerIOMappings(drivers);
    }
} //namespace src::Control

#endif