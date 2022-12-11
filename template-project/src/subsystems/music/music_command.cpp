#include "music_command.hpp"

namespace music{

MusicCommand::MusicCommand(MusicSubsystem *music, src::Drivers *drivers) :
    music(music), drivers(drivers), score(getScore()), position(0), tempo(quarterNoteLength) {}

void MusicCommand::initialize(){music->play(0); } //silences buzzer

void MusicCommand::execute() {
    if((score[position]).first < 0) finished = true;
    else{
    music->play((score[position]).first);
    modm::delay_us(tempo * (score[position]).second);
    position++;
    }
}

void MusicCommand::end(bool){music ->play(0);} //silences buzzer

bool MusicCommand::isFinished() const {return finished;}

}//namespace music
