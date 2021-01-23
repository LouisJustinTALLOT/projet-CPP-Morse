#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

#include "to_audio.hpp"

// g++ to_audio.cpp -g -o to_audio

// using namespace std;

// constants used to write WAV file
constexpr double two_pi = 6.283185307179586476925286766559;
constexpr double max_amplitude = 32760;  // "volume"

double hz        = 44100;   // samples per second
double frequency = 440;     // A3
double dot_duration = 0.2 ; // seconds

template <typename Word>
std::ostream& write_word( std::ostream& outs, Word value, unsigned size){
    for (; size; --size, value >>= 8)
        outs.put( static_cast <char> (value & 0xFF) );
    return outs;
}

size_t create_file(std::ostream& f){
    // Write the file headers
    f << "RIFF----WAVEfmt ";     // (chunk size to be filled in later)
    write_word( f,     16, 4 );  // no extension data
    write_word( f,      1, 2 );  // PCM - integer samples
    write_word( f,      2, 2 );  // two channels (stereo file)
    write_word( f,  44100, 4 );  // samples per second (Hz)
    write_word( f, 176400, 4 );  // (Sample Rate * BitsPerSample * Channels) / 8
    write_word( f,      4, 2 );  // data block size (size of two integer samples, one for each channel, in bytes)
    write_word( f,     16, 2 );  // number of bits per sample (use a multiple of 8)

      // Write the data chunk header
    size_t data_chunk_pos = f.tellp();
    f << "data----";  // (chunk size to be filled in later)

    return data_chunk_pos;
}

void dash_wav(std::ofstream& f){
    double seconds = dot_duration*3; 
    int N = hz * seconds;  // total number of samples
    
    for (int n = 0; n < N; n++){
        double amplitude =  max_amplitude;
        double value     = sin( (two_pi * n * frequency) / hz );
        write_word( f, (int)(                 amplitude  * value), 2 );
        write_word( f, (int)((max_amplitude - amplitude) * value), 2 );
    }
}

void dot_wav(std::ofstream& f){
    double seconds = dot_duration; 
    int N = hz * seconds;  // total number of samples

    for (int n = 0; n < N; n++){
        double amplitude =  max_amplitude;
        double value     = sin( (two_pi * n * frequency) / hz );
        write_word( f, (int)(                 amplitude  * value), 2 );
        write_word( f, (int)((max_amplitude - amplitude) * value), 2 );
    }
}

void short_space_wav(std::ofstream& f){
    double seconds = dot_duration; 
    int N = hz * seconds;  // total number of samples

    for (int n = 0; n < N; n++){
        write_word( f, (int)(0), 2 );
        write_word( f, (int)(0), 2 );
    }
}

void space_wav(std::ofstream& f){
    double seconds = dot_duration*6; 
    int N = hz * seconds;  // total number of samples

    for (int n = 0; n < N; n++){
        write_word( f, (int)(0), 2 );
        write_word( f, (int)(0), 2 );
    }
}

void finish_file(std::ofstream& f, size_t data_chunk_pos){
    // (We'll need the final file size to fix the chunk sizes above)
    size_t file_length = f.tellp();

    // Fix the data chunk header to contain the data size
    f.seekp( data_chunk_pos + 4 );
    write_word( f, file_length - data_chunk_pos + 8, sizeof(size_t) );

    // Fix the file header to contain the proper RIFF chunk size, which is (file size - 8) bytes
    f.seekp( 0 + 4 );
    write_word( f, file_length - 8, 4 ); 
}
/*
int main(){

    std::ofstream f( "output2.wav", std::ios::binary );   

    size_t data_chunk_pos = create_file(f);
    dot_wav(f);
    space_wav(f);
    dash_wav(f);
    short_space_wav(f);
    dot_wav(f);
    short_space_wav(f);
    dash_wav(f);
    short_space_wav(f);
    dash_wav(f);
    space_wav(f); 
    short_space_wav(f);
    dot_wav(f);
    short_space_wav(f);
    dot_wav(f);
    short_space_wav(f);
    dot_wav(f);
    short_space_wav(f);
    finish_file(f, data_chunk_pos);

    return 0; 
}
*/