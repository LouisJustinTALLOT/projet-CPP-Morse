#include <fstream>
#include <iostream>


// g++ test_wav_read.cpp -o test_wav_read

// template <typename Word>
// std::istream& read_word( std::istream& ins, Word value, unsigned size){

//     for (; size; --size, value >>= 8)
//     ins.get( static_cast <char> (value & 0xFF) );
//     return ins;
// }



int main(){

    std::ifstream f( "test_1.wav", std::ios::binary );

    char c1;

    int i = 0;
    while (true){          // loop getting single characters
        
        int c1 = f.get();
        i++;
        std::cout <<std::hex<< (int)c1<<" ";
        if (i%16==0){
            std::cout<<std::endl;
        }
        if (i>100){
            std::cout<<std::endl;
            return 0;
        }
    }


    return 0;
}
