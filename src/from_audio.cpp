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

std::string data_to_Morse(std::vector<int> data){
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
    
    for (int i=0; i<len-40; i++){

        if(i<100){
            std::cout<<"i "<<i<<" "<<min_length<<std::endl;
        }

        if (data[i]==0 && data[i+1]==0 && data[i+2]==0 && data[i+3]==0 &&data[i+4]==0 && data[i+5]==0 && data[i+6]==0 && data[i+7]==0){
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
                    parts_length.push_back(end-beg);
                    if (end-beg < min_length){
                        min_length = end-beg;
                    }
                    beg = i;
                }
            }
            
        }
        else {
            if (not in_a_space){
                change = false;
            }
            else{
                change = true;
                // std::cout<<"lalal "<<i<<" "<<beg<<std::endl;
            }
            in_a_space = false;

            if (i>10){
                end = i;
                
                if (change){
                    parts_length.push_back(end-beg);
                    if (end-beg < min_length){
                        min_length = end-beg;
                    }
                    beg = i;
                }
            }
            
            
        }

    }
    std::cout<<parts_length.size()<<std::endl<<std::endl;
    std::cout<<min_length<<std::endl<<std::endl;
    for (int x : parts_length){
        std::cout<<x<<"\n";
    }

    return Morse;
}



int main(){
    std::ifstream f("test_1.wav", std::ios::binary);
    // std::cout<<"here"<<std::endl;
    std::vector<int> a = file_data(f);
    std::cout<<data_to_Morse(a)<<std::endl;


    return 0;
}