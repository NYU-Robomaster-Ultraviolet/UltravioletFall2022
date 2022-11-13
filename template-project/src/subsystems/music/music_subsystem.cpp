
#include "music_subsystem.hpp"
using namespace tap;
using namespace tap::buzzer;
namespace music{

MusicSubsystem::MusicSubsystem(tap::Drivers *drivers) : 
tap::control::Subsystem(drivers) {}
//silences buzzer on initialization
void MusicSubsystem::initialize(){playNote(&(drivers->pwm), 0);}

void MusicSubsystem::refresh() {}

void MusicSubsystem::play(int32_t note) {
    playNote(&(drivers->pwm), note);
    drivers->leds.set(drivers->leds.Red, true);
}
}//namespace music
