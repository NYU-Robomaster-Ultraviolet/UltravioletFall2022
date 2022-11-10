#ifndef FEEDER_COMMAND_HPP_
#define FEEDER_COMMAND_HPP_

#include "tap/control/command.hpp"

#include "feeder_subsystem.hpp"
#include "drivers.hpp"

#include "tap/control/subsystem.hpp"
#include "modm/math/filter/pid.hpp"
#include "tap/motor/dji_motor.hpp"
#include "tap/util_macros.hpp"
#include "controls/standard/standard_constants.hpp"

namespace feeder{

class FeederCommand:public tap::control::Command{
public:
    /**
     * Initializes the command with the passed in FeederSubsystem.  Must not
     * be nullptr.
     *
     * @param[in] feeder a pointer to the feeder to be passed in that this
     *      Command will interact with.
     */
    FeederCommand(FeederSubsystem *const feeder, src::Drivers *drivers);

    FeederCommand(const FeederCommand &other) = delete;

    FeederCommand &operator=(const FeederCommand &other) = delete;

    void initialize() override;

    const char *getName() const { return "feeder command"; }

    void execute() override;

    void end(bool) override;

    bool isFinished() const override;
private:
    FeederSubsystem *const feeder;

    src::Drivers *drivers;
}; //class FeederCommand : public tap::control::Command
} //namespace feeder
#endif 