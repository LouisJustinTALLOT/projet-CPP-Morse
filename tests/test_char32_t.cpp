#include <iostream>
#include <string>

//g++ test_char32_t.cpp -o test_char32_t

int main(){

    const char32_t* test = U"zfzpofééé";

    std::u32string my_string = U"abcdefghijklmnopqrstuvwxyz é@\u0309s";
    
    // for (int i=0; i<sizeof(test)/sizeof(char32_t); i++){
    //     std::cout<<test[i]<<std::endl;
    // }

    for(char32_t x:my_string){
        
        std::cout<<x<<std::endl;
    }


    return 0;
}   