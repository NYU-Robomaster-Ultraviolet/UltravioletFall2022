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
using tap::communication::serial::Remote;

namespace src::control{
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
    chassis.setDefaultCommand((&chassisMovementCommand));
}
// Set Commands scheduled on startup
void startupCommands(src::Drivers* drivers) {
    

}
// Register IO mappings here -----------------------------------------------
void registerIOMappings(src::Drivers* drivers) {
    
}
}//namespace StandardControl


// Initialize subsystems ---------------------------------------------------
namespace src::control
{
    void initializeSubsystemCommands(src::Drivers* drivers)
    {
        initializeSubsystems();
        registerSubsystems(drivers);
        setDefaultCommands(drivers);
        startupCommands(drivers);
        registerIOMappings(drivers);
    }
} //namespace src::control

#endif