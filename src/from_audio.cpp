#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

#include "from_audio.hpp"

// g++ from_audio.cpp -g -o from_audio


std::vector<int> file_data(std::ifstream& f){
    // get the data from the wave file

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

std::string data_to_Morse(std::vector<int> data){
    // transform the data from wave file to Morse
    // by analyzing and detecting the various patterns

    std::string Morse = ""; 

    int len = int(data.size());// length of WAV file
    
    if (len<10){
        return Morse;
    }

    int min_length = len;
    int beg = 0;
    int end;
    bool in_a_space=false;
    bool change = false;

    std::vector<int> parts_length;
    std::vector<bool> space_or_not;
    
    for (int i=0; i<len-40; i++){

        if (data[i]==0 && data[i+1]==0 && data[i+2]==0 && data[i+3]==0 &&data[i+4]==0 && data[i+5]==0 && data[i+6]==0 && data[i+7]==0){

            // then we are in a space
            if (in_a_space){
                change = false;
            }
            else {
                change = true;
            }
            // we are in a space
            in_a_space = true;
            if (i>10){
                end = i;
                
                if (change){
                    parts_length.push_back(end-beg); // we add the new part
                    space_or_not.push_back(false); // we begin a "not space"

                    if (end-beg < min_length){
                        min_length = end-beg;
                    }
                    beg = i;
                }
            }
        }
        else {
            // then we are in a dot or a dash

            if (not in_a_space){
                change = false;
            }
            else{
                change = true;
            }
            in_a_space = false;

            if (i>10){
                end = i;
                
                if (change){
                    parts_length.push_back(end-beg); // we add the new part
                    space_or_not.push_back(true); // we begin a space

                    if (end-beg < min_length){
                        min_length = end-beg;
                    }
                    beg = i;
                }
            }
        }
    }
    // we will now create Morse code from the gathered info

    for (int i =0; i<int(parts_length.size()); i++){
        // std::cout<<parts_length[i]<<" "<<space_or_not[i]<<std::endl;
        if (space_or_not[i]){// then it was a space

            if (abs(parts_length[i]-min_length)<100){
                // then it is the smallest space, the one between characters -> nothing
                Morse += "";
            }
            else if (abs(parts_length[i]- 2*min_length)<100){
                Morse += " ";
            }
            else{
                Morse += "   ";
            }
        }
        else {
            if (abs(parts_length[i]-min_length)<100){
                // then it is a dot 
                Morse += ".";
            }
            else{
                Morse += "-";
            }

        }
    }

    return Morse;
}

/*

int main(){
    std::ifstream f("test_1.wav", std::ios::binary);
    // std::cout<<"here"<<std::endl;
    std::vector<int> a = file_data(f);
    std::cout<<data_to_Morse(a)<<std::endl;


    return 0;
}

*/