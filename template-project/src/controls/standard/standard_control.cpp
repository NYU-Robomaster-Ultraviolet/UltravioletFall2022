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
#include "subsystems/gimbal/gimbal_subsystem.hpp"
#include "subsystems/music/music_subsystem.hpp"

#include "subsystems/chassis/chassis_movement_command.hpp"
#include "subsystems/gimbal/gimbal_movement_command.hpp"
#include "subsystems/music/music_command.hpp"


src::driversFunc drivers = src::DoNotUse_getDrivers;

using namespace tap;
using namespace tap::control;
using namespace tap::communication::serial;
using namespace chassis;
using namespace gimbal;
using namespace music;

namespace src::control{
// Define subsystems here ------------------------------------------------
ChassisSubsystem chassis(drivers());
GimbalSubsystem gimbal(drivers());
MusicSubsystem music(drivers());
// Robot Specific Controllers ------------------------------------------------

// Define commands here ---------------------------------------------------
ChassisMovementCommand chassisMovement(&chassis, drivers());
GimbalMovementCommand gimbalMovement(&gimbal, drivers());
MusicCommand musicPlayer(&music, drivers());
// Define command mappings here -------------------------------------------
HoldCommandMapping rightSwitchMid(drivers(), {&chassisMovement, &gimbalMovement}, 
RemoteMapState(Remote::Switch::RIGHT_SWITCH, Remote::SwitchState::MID));

HoldCommandMapping rightSwitchUp(drivers(), {&gimbalMovement}, 
RemoteMapState(Remote::Switch::RIGHT_SWITCH, Remote::SwitchState::UP));
// Register subsystems here -----------------------------------------------
void registerSubsystems(src::Drivers *drivers){
    drivers->commandScheduler.registerSubsystem(&chassis);
    drivers->commandScheduler.registerSubsystem(&gimbal);
    drivers->commandScheduler.registerSubsystem(&music);
}
// Initialize subsystems here ---------------------------------------------
void initializeSubsystems() {
    chassis.initialize();
    gimbal.initialize();
    music.initialize();
}
// Set default command here -----------------------------------------------
void setDefaultCommands(src::Drivers* drivers) {
    //chassis.setDefaultCommand(&chassisMovement);
    music.setDefaultCommand(&musicPlayer);
}
// Set Commands scheduled on startup
void startupCommands(src::Drivers* drivers) {

}
// Register IO mappings here -----------------------------------------------
void registerIOMappings(src::Drivers* drivers) {
    drivers->commandMapper.addMap(&rightSwitchMid);
    drivers->commandMapper.addMap(&rightSwitchUp);
}
}//namespace src::control


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
} //namespace src::Control

#endif