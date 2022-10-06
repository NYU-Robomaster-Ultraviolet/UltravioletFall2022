/*
#ifndef MUSIC_COMMAND_HPP_
#define MUSIC_COMMAND_HPP_

#include "tap/control/command.hpp"
#include "music_subsystem.hpp"
#include "drivers.hpp"
#include "vector"

#endif

class MusicCommand : tap::control::Command{
    public:
        MusicCommand(MusicSubsystem *const music, src::Drivers *drivers, std::vector<uint32_t>* score);

        void initialize() override;

        const char *getName() const { return "music command"; }

        void execute() override;

        void end(bool) override;

        bool isFinished() const override;
    private:
        MusicSubsystem* const music;
        src::Drivers* drivers;
        std::vector<uint32_t>* score;
        
};
*/