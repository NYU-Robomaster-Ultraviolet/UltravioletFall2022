#ifndef SONGS_HPP_
#define SONGS_HPP_

#include "vector"
#include "map"
#include "notes.hpp"
#include "music_scores/cyber_angel.hpp"

using namespace std;

namespace music{
//Make objects of the structs representing all notes from their octave in frequency
//This is the tempo to be used in your song this only works for x/4 time
class MusicDisk{
public:
    vector<pair<float, float>> getScore() const {return yourSong;}
    void setScore(vector<pair<float, float>> song) {yourSong = song;}
private:


vector<pair<float, float>> yourSong = YOURSONG;

};
}//namespace music

#endif