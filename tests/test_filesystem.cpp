#include <iostream>
#include <filesystem>

// g++ -std=c++17 test_filesystem.cpp -o test_filesystem

std::size_t number_of_files_in_directory(std::filesystem::path path){
    return (std::size_t)std::distance(std::filesystem::directory_iterator{path}, std::filesystem::directory_iterator{});
}


int main(){

    std::size_t a;
    std::filesystem::path p ="../src";

    a = number_of_files_in_directory(p);
    std::cout<<a<<std::endl;


    return 0;
}