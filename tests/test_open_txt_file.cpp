#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>

// g++ test_open_txt_file.cpp -o test_open_txt_file

int main(){


    std::ifstream t("test_1.txt");
    std::string str((std::istreambuf_iterator<char>(t)),
                 std::istreambuf_iterator<char>());

    std::cout<< str << std::endl;

    return 0;
}