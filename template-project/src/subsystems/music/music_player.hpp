#ifndef MUSIC_PLAYER_HPP_
#define MUSIC_PLAYER_HPP_

#include "drivers.hpp"
#include "vector"
#include "tap/communication/sensors/buzzer/buzzer.hpp"
#include "songs.hpp"

using namespace tap;
using namespace tap::buzzer;

namespace music{

class MusicPlayer{
    public:
        MusicPlayer(src::Drivers *drivers, MusicDisk score);

        void execute();

    private:
        src::Drivers* drivers;
        MusicDisk score;
        const unsigned tempo;
};
} //namespace music

#endif