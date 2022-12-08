#ifndef SONGS_HPP_
#define SONGS_HPP_

#include "vector"
#include "map"
#include "notes.hpp"

using namespace std;

namespace music{
//Make objects of the structs representing all notes from their octave in frequency
//This is the tempo to be used in your song this only works for x/4 time
static const unsigned TEMPO = 166; //in ms this is = 60 BPM
static const unsigned QUARTERNOTELENGTH = 60000 / TEMPO; //60000 = 1 min in ms
class MusicDisk{
public:
        vector<pair<float, float>> getScore() const {return yourSong;}
private:
    Octave0 O0;
    Octave1 O1;
    Octave2 O2;
    Octave3 O3;
    Octave4 O4;
    Octave5 O5;
    Octave6 O6;
    Octave7 O7;
    NoteType N;


    /*this is the vector that contains your song. Each element of the vector are floats
The first: containing the note to be played, see the notes.hpp file to see the frequencies used.
    For example, if you want to use the note C in the 3rd octave use O3.C for your note
The second: represents the amount of time that a note should be played for. This value will be multiplied by
    your tempo, so a value of 1.0f will represent a quarter rest given 4/4 time.
Note: If you want a rest, put the note value as 0.0f
*/
vector<pair<float, float>> yourSong{
    
//Never Surrender - Mizuki Nana

//measure 1
pair<float, float>(O5.C, N.E),
pair<float, float>(O4.G, N.E),
pair<float, float>(O4.E, N.E),  
pair<float, float>(O4.B, N.E),
pair<float, float>(O4.G, N.E),  
pair<float, float>(O4.D, N.E),
pair<float, float>(O4.G, N.E),  
pair<float, float>(O4.D, N.E),

//measure 2
pair<float, float>(O3.B, N.E),  
pair<float, float>(O4.E, N.DQ),
pair<float, float>(0, N.H),

//measure 3
pair<float, float>(O5.C, N.E),
pair<float, float>(O4.G, N.E),
pair<float, float>(O4.E, N.E),  
pair<float, float>(O4.B, N.E),
pair<float, float>(O4.G, N.E),  
pair<float, float>(O4.D, N.E),
pair<float, float>(O4.G, N.E),  
pair<float, float>(O4.D, N.E),

//measure 4
pair<float, float>(O3.B, N.E),  
pair<float, float>(O4.E, N.DQ),
pair<float, float>(0, N.H),

//measure 5
pair<float, float>(O4.G, N.DQ),  
pair<float, float>(O4.F, N.DQ),
pair<float, float>(O4.E, N.Q), 

//measure 6 
pair<float, float>(O4.C, N.DQ),
pair<float, float>(O4.D, N.DQ),  
pair<float, float>(O3.A, N.Q),

//measure 7
pair<float, float>(O4.E, N.H),  
pair<float, float>(0, N.E),
pair<float, float>(O3.A, N.E),  
pair<float, float>(O4.E, N.E),
pair<float, float>(O4.A, N.E), 

//measure 8
pair<float, float>(O5.E, N.W),

//measure 9
pair<float, float>(0, N.DQ),  
pair<float, float>(O3.DS, N.E),
pair<float, float>(O3.E, N.E),  
pair<float, float>(O3.A, N.E),
pair<float, float>(O4.E, N.E), 

pair<float, float>(O4.D, N.DQ), //measure 10 
pair<float, float>(O4.C, N.E),  
pair<float, float>(O3.B, N.Q),
pair<float, float>(O3.A, N.Q), 

pair<float, float>(O3.B, N.Q), //measure 11
pair<float, float>(O4.C, N.E),  
pair<float, float>(O4.D, N.E),
pair<float, float>(O3.B, N.Q),  
pair<float, float>(O3.G, N.E),
pair<float, float>(O3.D, N.E),

pair<float, float>(O3.E, N.DQ), //measure 12
pair<float, float>(0, N.E),  
pair<float, float>(O4.A, N.S),
pair<float, float>(O4.B, N.S),  
pair<float, float>(O5.C, N.E),
pair<float, float>(O4.B, N.E),  
pair<float, float>(O4.G, N.E),

pair<float, float>(O4.D, N.Q), //measure 13
pair<float, float>(O4.C, N.E),
pair<float, float>(O3.B, N.S),  
pair<float, float>(0, N.S),
pair<float, float>(O3.E, N.E),  
pair<float, float>(O3.G, N.E),
pair<float, float>(O3.B, N.E),  
pair<float, float>(O4.E, N.E),

pair<float, float>(O4.G, N.DQ), //measure 14
pair<float, float>(O4.F, N.E),
pair<float, float>(O4.E, N.Q),  
pair<float, float>(O4.F, N.E),
pair<float, float>(O4.E, N.E), 

pair<float, float>(O4.D, N.DQ), //measure 15
pair<float, float>(O3.G, N.E),  
pair<float, float>(O4.D, N.Q),
pair<float, float>(O3.B, N.E),

pair<float, float>(O3.G, N.E + N.H), //measure 16
pair<float, float>(O3.G, N.S),  
pair<float, float>(O3.A, N.S),
pair<float, float>(O3.B, N.S), 
pair<float, float>(O4.C, N.S), 
pair<float, float>(O4.D, N.S),  
pair<float, float>(O4.E, N.S),

pair<float, float>(O4.F, N.Q), //measure 17 
pair<float, float>(O4.E, N.E), 
pair<float, float>(O4.G, N.E),  
pair<float, float>(O4.F, N.Q), 
pair<float, float>(O3.B, N.E),
pair<float, float>(O4.D, N.E), 
pair<float, float>(O4.F, N.E), 

//measure 18
pair<float, float>(O4.E, N.Q), 
pair<float, float>(0, N.E), 
pair<float, float>(O4.F, N.Q), 
pair<float, float>(0, N.E), 
pair<float, float>(O4.G, N.Q), 

//measure 19 (2/4)
pair<float, float>(0, N.E), 
pair<float, float>(O4.GS, N.Q), 
pair<float, float>(0, N.E),

//measure 20
pair<float, float>(O4.G, N.S),
pair<float, float>(O4.FS, N.S),
pair<float, float>(O4.F, N.S),
pair<float, float>(O4.E, N.S),
pair<float, float>(O4.DS, N.S),
pair<float, float>(O4.D, N.S),
pair<float, float>(O4.CS, N.S),
pair<float, float>(O4.C, N.S),
pair<float, float>(O3.B, N.S),
pair<float, float>(O3.AS, N.S),
pair<float, float>(O3.A, N.S),
pair<float, float>(O3.GS, N.S),
pair<float, float>(O3.G, N.S),
pair<float, float>(O3.FS, N.S),
pair<float, float>(O3.F, N.S),
pair<float, float>(O3.E, N.S)
//measure 21
};//yourSong
};
}//namespace music

#endif