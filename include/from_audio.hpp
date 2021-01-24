#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>


std::vector<int> file_data(std::ifstream& f);
std::string data_to_Morse(std::vector<int> data);

