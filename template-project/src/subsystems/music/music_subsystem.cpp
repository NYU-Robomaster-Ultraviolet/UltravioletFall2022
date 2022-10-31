
#include "music_subsystem.hpp"
using namespace tap;
using namespace tap::buzzer;

MusicSubsystem::MusicSubsystem(tap::Drivers *drivers) : 
tap::control::Subsystem(drivers) {}

void MusicSubsystem::initialize(){}

void MusicSubsystem::refresh() {}

void MusicSubsystem::play(int32_t note) {
    playNote(&(drivers->pwm), note);
}
