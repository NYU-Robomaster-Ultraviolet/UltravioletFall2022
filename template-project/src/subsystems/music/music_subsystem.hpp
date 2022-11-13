#ifndef MUSIC_SUBSYSTEM_HPP_
#define MUSIC_SUBSYSTEM_HPP_

#include "tap/control/subsystem.hpp"
#include "tap/communication/sensors/buzzer/buzzer.hpp"
#include "drivers.hpp"

using namespace tap::buzzer;

namespace music{
//The music subsystem class will play a series of sounds of different 
// frequencies based on the defined robot
class MusicSubsystem : public tap::control::Subsystem{
    public:
        MusicSubsystem(tap::Drivers *drivers);

        MusicSubsystem &operator=(const MusicSubsystem &other) = delete;

        ~MusicSubsystem() = default;

        void initialize() override;

        void refresh() override;

        void play(int32_t note);

    private:
};
}//namespace music

#endif
