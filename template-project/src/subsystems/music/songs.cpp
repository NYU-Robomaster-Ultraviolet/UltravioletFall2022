#include "songs.hpp"

namespace music{
//structs for notes
Octave0 O0;
Octave1 O1;
Octave2 O2;
Octave3 O3;
Octave4 O4;
Octave5 O5;
Octave6 O6;
Octave7 O7;


/*this is the vector that contains your song. Each element of the vector are floats
The first: containing the note to be played, see the notes.hpp file to see the frequencies used.
    For example, if you want to use the note C in the 3rd octave use O3.C for your note
The second: represents the amount of time that a note should be played for. This value will be multiplied by
    your tempo, so a value of 1.0f will represent a quarter rest given 4/4 time.
Note: If you want a rest, put the note value as 0.0f
Note: a value of -1.0f should be inputed if you wish to dictate the end of the song
*/
vector<pair<float, float>> yourSong{
pair<float, float>(O3.C, 30.0f), //arbitrary value, replace with what you would like
pair<float, float>(O3.F, 30.0f),
pair<float, float>(0.0f, 0.0f), //silences buzzer
pair<float, float>(-1.0f, 0.0f) //This is the end of the song
};

vector<pair<float, float>> getScore(){return yourSong;}
}//namespace music