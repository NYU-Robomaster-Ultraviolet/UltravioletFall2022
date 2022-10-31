#ifndef NOTES__HPP__
#define NOTES__HPP__

//these are the frequencies of common notes sorted by octave in a struct
//Note: S = Sharp
struct Octave0 {
    static constexpr float C = 16.35f, CS = 17.32f, D = 18.35f, DS = 19.45f, E = 20.60f,
    F = 21.83f, FS = 23.12f, G = 24.5f, GS = 25.96f, A = 27.5f, AS = 29.14f, B = 30.87f;
    };//struct O0
struct Octave1 {
    static constexpr float C = 32.7f, CS = 34.65f, D = 36.71f, DS = 38.89f, E = 41.2f,
    F = 43.65f, FS = 46.25f, G = 49.0f, GS = 51.91f, A = 55.0f, AS = 58.27f, B = 61.74f;
    };//struct O1
struct Octave2 {
    static constexpr float C = 65.41f, CS = 69.30f, D = 73.42f, DS = 77.78f, E = 82.41f,
    F = 87.31f, FS = 92.5f, G = 98.0f, GS = 103.83f, A = 110.0f, AS = 116.54f, B = 123.47f;
    };//struct O2
struct Octave3 {
    static constexpr float C = 130.81f, CS = 138.59f, D = 146.83f, DS = 155.56f, E = 164.81f,
    F = 174.61f, FS = 185.0f, G = 196.0f, GS = 207.65f, A = 220.0f, AS = 233.08f, B = 246.94f;
    };//struct O3
struct Octave4 {
    static constexpr float C = 261.63f, CS = 277.18f, D = 293.66f, DS = 311.13f, E = 329.63f,
    F = 349.23f, FS = 369.99f, G = 392.0f, GS = 415.3f, A = 440.0f, AS = 466.16f, B = 493.88f;
    };//struct O4
struct Octave5 {
    static constexpr float C = 523.25f, CS = 554.37f, D = 587.33f, DS = 622.25f, E = 659.25f,
    F = 698.46f, FS = 739.99f, G = 783.99f, GS = 830.61f, A = 880.0f, AS = 932.33f, B = 987.77f;
    };//struct O5
struct Octave6 {
    static constexpr float C = 1046.5f, CS = 1108.73f, D = 1174.66f, DS = 1244.51f, E = 1318.51f,
    F = 1396.91f, FS = 1479.98f, G = 1567.98f, GS = 1661.22f, A = 1760.0f, AS = 1864.66f, B = 1975.53f;
    };//struct O6
struct Octave7 {
    static constexpr float C = 2093.0f, CS = 2217.46f, D = 2349.32f, DS = 2489.02f, E = 2637.02f,
    F = 2793.83f, FS = 2959.96f, G = 3135.96f, GS = 3322.44f, A = 3520.0f, AS = 3729.31f, B = 3951.07f;
    };//struct O7
#endif