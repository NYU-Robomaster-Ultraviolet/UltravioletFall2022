
#include "music_command.hpp"

MusicCommand::MusicCommand(MusicSubsystem *music, src::Drivers *drivers) :
    music(music), drivers(drivers), score(yourSong), position(0), tempo(BPM) {}

void MusicCommand::initialize(){}

void MusicCommand::execute() {
    if((score[position]).first < 0) finished = true;
    else{
    music->play((score[position]).first);
    modm::delay_us(tempo * (score[position]).second);
    position++;
    }
}

void MusicCommand::end(bool){}

bool MusicCommand::isFinished() const {return finished;}
