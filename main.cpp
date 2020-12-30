#include <iostream>
#include <string>
#include <map>
#include <algorithm>

const std::string WHITESPACE = " \n\r\t\f\v";

std::string ltrim(const std::string& s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}
 
std::string rtrim(const std::string& s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}
 
std::string trim(const std::string& s)
{
    return rtrim(ltrim(s));
}

std::map <std::string, std::string> create_dict_morse_to_car(){
    std::map <std::string, std::string> m;

    m[""] = "";
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
    m["-----"] = "0";
    m[".----"] = "1";
    m["..---"] = "2";
    m["...--"] = "3";
    m["....-"] = "4";
    m["....."] = "5";
    m["-...."] = "6";
    m["--..."] = "7";
    m["---.."] = "8";
    m["----."] = "9";
    m[".-.-.-"] = ".";
    m["--..--"] = ",";
    m["..--.."] = "?";
    m[".----."] = "'";
    m["-.-.--"] = "!";
    m["-..-."] = "/";
    m["-.--."] = "(";
    m["-.--.-"] = ")";
    m["&"] = ".-...";

    return m;
}

std::map <std::string, std::string> create_dict_car_to_morse(){
    std::map <std::string, std::string> mtc = create_dict_morse_to_car();
    std::map <std::string, std::string> m;

    for (auto item: mtc){
        // std::cout<<item.first<<" -> "<<item.second<<std::endl;
        m[item.second] = item.first;
    }
    m[" "] = "   ";

    return m;
}


std::string Morse_to_text(std::string morse, 
                        std::map <std::string, std::string> dict_morse_car = create_dict_morse_to_car()){
    std::string res = "";
    std::string temp = "";

    // we first trim the leading and trailing spaces of morse text
    morse = trim(morse);

    for(int i=0; i<morse.length(); i++ ){
        // for each character we check whether it is a space or not 
        // if yes it is the end of a letter
        // but it could also be a space between words =  3 spaces in Morse

        if (morse[i] == ' ' ){  
            if (i+1 < morse.length() and morse[i+1] != ' '){
                // it's the end of a character
                res += dict_morse_car[temp];
                temp = "";
            }
            else if (i>0 and morse[i-1] != ' '){
                // it's the end of a character 
                res += dict_morse_car[temp];
                temp = "";
            }
            if (i>0 and morse[i-1] == ' '){
                // we're in the middle of a space -> do nothing
            }
            if (i>1 and morse[i-1] == ' ' and morse[i-2] == ' '){
                // we're at the end of a space
                res += " ";
            }
        }
        else if (i+1 == morse.length()){
            // it's the end of the text and of a character
            temp += morse[i];
            res += dict_morse_car[temp];
        }
        else
        {
            // we're in the middle of a character
            temp += morse[i];
        }
    }

    return res;
}

std::string text_to_Morse(std::string text, 
                        std::map <std::string, std::string> dict_car_morse = create_dict_car_to_morse()){
    std::string res = "";
    dict_car_morse[" "] = "  ";
    text = trim(text);

    for (int i = 0; i<text.length(); i++){
        std::string car (1,text[i]);
        std::map <std::string, std::string>::const_iterator pos = dict_car_morse.find(car);
    
        res += pos->second;
        res += " ";
    }

    return res;
}

int main(){


    std::map <std::string, std::string> dict_morse_car = create_dict_morse_to_car();
    std::map <std::string, std::string> dict_car_morse = create_dict_car_to_morse();
   

    std::string test_morse_1 = ".... . .-.. .-.. ---     .-- --- .-. .-.. -..";
    std::cout<<Morse_to_text(test_morse_1, dict_morse_car)<<std::endl;
    std::string test_text_1 = "hello world !";
    std::cout<<text_to_Morse(test_text_1, dict_car_morse)<<std::endl;

    return 0;
}