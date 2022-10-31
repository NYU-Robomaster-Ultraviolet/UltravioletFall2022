#ifndef SONGS_HPP_
#define SONGS_HPP_

#include "vector"
#include "map"
#include "notes.hpp"

using namespace std;

namespace music{
//Make objects of the structs representing all notes from their octave in frequency
//This is the tempo to be used in your song
static const unsigned BPM = 100; //in ms this is = 60 BPM
vector<pair<float, float>> getScore();
}//namespace music

#endif