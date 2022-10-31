#ifndef MUSIC_COMMAND_HPP_
#define MUSIC_COMMAND_HPP_

#include "tap/control/command.hpp"
#include "music_subsystem.hpp"
#include "drivers.hpp"
#include "vector"
#include "tap/communication/sensors/buzzer/buzzer.hpp"
#include "songs.hpp"

using namespace tap;
using namespace tap::buzzer;

namespace music{

class MusicCommand : tap::control::Command{
    public:
        MusicCommand(MusicSubsystem *music, src::Drivers *drivers);

        void initialize() override;

        const char *getName() const { return "music command"; }

        void execute() override;

        void end(bool) override;

        bool isFinished() const override;
    private:
        MusicSubsystem* music;
        src::Drivers* drivers;
        std::vector<pair<float, float>> score;
        size_t position;
        unsigned tempo;
        bool finished = false;
};
} //namespace music

#endif