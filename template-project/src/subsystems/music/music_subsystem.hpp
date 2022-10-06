/*
#ifndef MUSIC_SUBSYSTEM_HPP_
#define MUSIC_SUBSYSTEM_HPP_

#include "tap/control/subsystem.hpp"
#include "tap/communication/sensors/buzzer/buzzer.hpp"

using namespace tap::buzzer;
static int beat = 100; //in ms

//The music subsystem class will play a series of sounds of different 
// frequencies based on the defined robot
class MusicSubsystem : tap::control::Subsystem{
    public:
        MusicSubsystem(tap::Drivers *drivers);

        MusicSubsystem &operator=(const MusicSubsystem &other) = delete;

        ~MusicSubsystem() = default;

        void initialize() override;

        void refresh() override;

        void play_note(int32_t note);

    private:
        int tempo;
        //tap::gpio::Pwm* buzzer;
};

#endif
*/