#include <iostream>
#include <string>
#include <map>

std::map <std::string, std::string> create_dict_morse_to_car(){
    std::map <std::string, std::string> m;
    m[".-"] = "a";
    m["-..."] = "b";
    m["-.-."] = "c";
    m["-.."] = "d";
    m["."] = "e";
    m["..-."] = "f";
    m["--."] = "g";
    m["...."] = "h";
    m[".."] = "i";
    m[".---"] = "j";
    m["-.-"] = "k";
    m[".-.."] = "l";
    m["--"] = "m";
    m["-."] = "n";
    m["---"] = "o";
    m[".--."] = "p";
    m["--.-"] = "q";
    m[".-."] = "r";
    m["..."] = "s";
    m["-"] = "t";
    m["..-"] = "u";
    m["...-"] = "v";
    m[".--"] = "w";
    m["-..-"] = "x";
    m["-.--"] = "y";
    m["--.."] = "z";
    // m[""] = "0";
    // m[""] = "1";
    // m[""] = "2";
    // m[""] = "3";
    // m[""] = "4";
    // m[""] = "5";
    // m[""] = "6";
    // m[""] = "7";
    // m[""] = "8";
    // m[""] = "9";
    // m[""] = "7";

    return m;
}

std::map <std::string, std::string> create_dict_car_to_morse(){
    std::map <std::string, std::string> mtc = create_dict_morse_to_car();
    std::map <std::string, std::string> m;

    for (auto item: mtc){
        // std::cout<<item.first<<" -> "<<item.second<<std::endl;
        m[item.second] = item.first;
    }

    return m;
}


std::string Morse_to_text(std::string morse, 
                        std::map <std::string, std::string> dict_morse_car = create_dict_morse_to_car()){
    std::string res = "";
    std::string temp = "";

    for(int i=0; i<morse.length(); i++ ){
        if (morse[i] == ' ' ){
            
            res += dict_morse_car[temp];
            temp = "";
        }
        else if (i+1 == morse.length()){
            temp += morse[i];
            res += dict_morse_car[temp];
        }
        else
        {
            temp += morse[i];
        }
        
    }

    return res;
}

int main(){


    std::map <std::string, std::string> dict_morse_car = create_dict_morse_to_car();
    std::map <std::string, std::string> dict_car_morse = create_dict_car_to_morse();
   

    return 0;
}