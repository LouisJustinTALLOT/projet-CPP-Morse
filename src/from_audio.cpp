#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// #include "from_audio.hpp"

// g++ from_audio.cpp -g -o from_audio


std::vector<int> file_data(std::ifstream& f){
    std::streampos len;
    f.seekg (0, std::ios::end);
    len = f.tellg(); // this is the length of the file

    std::vector<int> res;
    int c;
    
    // we start from 48 to get straight to the data part 
    // (by skipping the header)
    f.seekg(48, std::ios::beg);

    for (int i=0; i<int(len)-48; i++){
        c = f.get(); //-> it is an integer
        res.push_back(c);
    }

    return res;
}
