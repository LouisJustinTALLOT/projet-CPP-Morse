#pragma once

#include <string>
#include <cmath>
#include <fstream>
#include <iostream>


template <typename Word>
std::ostream& write_word( std::ostream& outs, Word value, unsigned size);
size_t create_file(std::ostream& f);
void dash_wav(std::ofstream& f);
void dot_wav(std::ofstream& f);
void short_space_wav(std::ofstream& f);
void space_wav(std::ofstream& f);
void finish_file(std::ofstream& f, size_t data_chunk_pos);