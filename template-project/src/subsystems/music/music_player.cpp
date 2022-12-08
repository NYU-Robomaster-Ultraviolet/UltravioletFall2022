#include "music_player.hpp"

namespace music{

MusicPlayer::MusicPlayer(src::Drivers *drivers, MusicDisk score) :
    drivers(drivers), score(score), tempo(QUARTERNOTELENGTH) {}

void MusicPlayer::execute() {
    vector<pair<float, float>> currDisk = score.getScore();
    drivers->leds.set(drivers->leds.Red, currDisk.size() < 100);
    drivers->leds.set(drivers->leds.Green, currDisk.size() > 100);
    for(size_t i = 0; i < currDisk.size(); i++){
        drivers->leds.set(drivers->leds.Blue, true);
        tap::buzzer::playNote(&drivers->pwm, (currDisk[i]).first);
        modm::delay_ms(tempo * (currDisk[i]).second * 0.8f);
        tap::buzzer::playNote(&(drivers->pwm), 0);
        modm::delay_ms(tempo * (currDisk[i]).second * 0.2f);
    }
    tap::buzzer::playNote(&(drivers->pwm), 0); //silences buzzer
    drivers->leds.set(drivers->leds.Blue, false);
    //drivers->leds.set(drivers->leds.Green, true);
}
}//namespace music
