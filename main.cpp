#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <locale>

std::u32string const WHITESPACE = U" \n\r\t\f\v";

std::u32string ltrim(const std::u32string& s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::u32string::npos) ? U"" : s.substr(start);
}
 
std::u32string rtrim(const std::u32string& s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::u32string::npos) ? U"" : s.substr(0, end + 1);
}
 
std::u32string trim(const std::u32string& s)
{
    return rtrim(ltrim(s));
}

std::u32string sanitize_entry(){}

int detect_entry_type(std::u32string entry){
    // returns :
    // 1 if text
    // 2 if Morse code
    // 3 if file to open
    entry = trim(entry);

    if (entry.find(U".txt") != std::u32string::npos){
        // then we have a (path to a) .txt file
        return 3;
    }
    if (entry[0]=='.' or entry[0] == '-'){
        // it's Morse
        return 2;
    }
    // it's text
    return 1; 
}

std::map <std::u32string, std::u32string> create_dict_morse_to_car(){
    std::map <std::u32string, std::u32string> m;

    m[U""]         = U"";
    m[U".-"]       = U"a";
    m[U"-..."]     = U"b";
    m[U"-.-."]     = U"c";
    m[U"-.."]      = U"d";
    m[U"."]        = U"e";
    m[U"..-."]     = U"f";
    m[U"--."]      = U"g";
    m[U"...."]     = U"h";
    m[U".."]       = U"i";
    m[U".---"]     = U"j";
    m[U"-.-"]      = U"k";
    m[U".-.."]     = U"l";
    m[U"--"]       = U"m";
    m[U"-."]       = U"n";
    m[U"---"]      = U"o";
    m[U".--."]     = U"p";
    m[U"--.-"]     = U"q";
    m[U".-."]      = U"r";
    m[U"..."]      = U"s";
    m[U"-"]        = U"t";
    m[U"..-"]      = U"u";
    m[U"...-"]     = U"v";
    m[U".--"]      = U"w";
    m[U"-..-"]     = U"x";
    m[U"-.--"]     = U"y";
    m[U"--.."]     = U"z";
    m[U"-----"]    = U"0";
    m[U".----"]    = U"1";
    m[U"..---"]    = U"2";
    m[U"...--"]    = U"3";
    m[U"....-"]    = U"4";
    m[U"....."]    = U"5";
    m[U"-...."]    = U"6";
    m[U"--..."]    = U"7";
    m[U"---.."]    = U"8";
    m[U"----."]    = U"9";
    m[U".-.-.-"]   = U".";
    m[U"--..--"]   = U",";
    m[U"..--.."]   = U"?";
    m[U".----."]   = U"'";
    m[U"-.-.--"]   = U"!";
    m[U"-..-."]    = U"/";
    m[U"-.--."]    = U"(";
    m[U"-.--.-"]   = U")";
    m[U".-..."]    = U"&";
    m[U"---..."]   = U":";
    m[U"-.-.-."]   = U";";
    m[U"-...-"]    = U"=";
    m[U".-.-."]    = U"+";
    m[U"-....-"]   = U"-";
    m[U"..--.-"]   = U"_";
    m[U"...-..-"]  = U"$";
    m[U".--.-."]   = U"@";
    m[U".-.-"]     = U"æ";
    m[U".--.-"]    = U"à";
    m[U"-.-.."]    = U"ç";
    m[U"..--."]    = U"ð";
    m[U".-..-"]    = U"è";
    m[U"..-.."]    = U"é";
    m[U"--.--"]    = U"ñ";
    m[U"---."]     = U"ø";
    m[U"..--"]     = U"ü";

    return m;
}

std::map <std::u32string, std::u32string> create_dict_car_to_morse(){
    std::map <std::u32string, std::u32string> mtc = create_dict_morse_to_car();
    std::map <std::u32string, std::u32string> m;

    for (auto item: mtc){
        // std::cout<<item.first<<" -> "<<item.second<<std::endl;
        m[item.second] = item.first;
    }
    m[U" "] = U"   ";
    m[U"ù"] = U"..-";

    return m;
}


std::u32string Morse_to_text(std::u32string morse, 
                        std::map <std::u32string, std::u32string> dict_morse_car = create_dict_morse_to_car()){
    std::u32string res  = U"";
    std::u32string temp = U"";

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
                temp = U"";
            }
            else if (i>0 and morse[i-1] != ' '){
                // it's the end of a character 
                res += dict_morse_car[temp];
                temp = U"";
            }
            if (i>0 and morse[i-1] == ' '){
                // we're in the middle of a space -> do nothing
            }
            if (i>1 and morse[i-1] == ' ' and morse[i-2] == ' '){
                // we're at the end of a space
                res += U" ";
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

std::u32string text_to_Morse(std::u32string text, 
                        std::map <std::u32string, std::u32string> dict_car_morse = create_dict_car_to_morse()){
    std::u32string res = U"";
    dict_car_morse[U" "] = U"  ";
    text = trim(text);

    std::locale loc;

    for (std::u32string::size_type i=0; i<text.length(); i++){
        text[i] = std::tolower(text[i], loc);
    }
    
    for (int i = 0; i<text.length(); i++){
        std::u32string car (1,text[i]);
        std::map <std::u32string, std::u32string>::const_iterator pos = dict_car_morse.find(car);
    
        res += pos->second;
        res += U" ";
    }

    return res;
}

int main(int argc, char *argv[]){
    std::u32string entry_text = U"";

    if(argc > 1){
        
        for (int i = 1; i<argc; i++){
            std::string temp(argv[i]);
            std::u32string temp2;
            temp2.assign(temp.begin(), temp.end());
            entry_text += temp2;
            if (i + 1 <argc){
                entry_text += U" ";
            }
        }
        std::cout<<std::endl<<entry_text.c_str()<<std::endl;
    }

    std::map <std::u32string, std::u32string> dict_morse_car = create_dict_morse_to_car();
    std::map <std::u32string, std::u32string> dict_car_morse = create_dict_car_to_morse();
   

    int entry_type = detect_entry_type(entry_text);

    if (entry_type == 1){
        // we have text -> Morse
        std::cout<<text_to_Morse(entry_text, dict_car_morse).c_str()<<std::endl;
    }
    else if (entry_type == 2){
        // we have Morse code
        std::cout<<Morse_to_text(entry_text, dict_morse_car).c_str()<<std::endl;
    }
    
    // various tests :
    std::cout<<"here\n";
    std::u32string test_morse_1 = U"    .... . .-.. .-.. ---   .-- --- .-. .-.. -..   -.-.--   ";
    std::cout<<Morse_to_text(test_morse_1, dict_morse_car).c_str()<<std::endl;
    std::u32string test_text_1 = U"     hello world !      ";
    std::cout<<text_to_Morse(test_text_1, dict_car_morse).c_str()<<std::endl;

    if (argc >1){
        std::cout<<std::endl<<detect_entry_type(entry_text)<<std::endl;
    }

    return 0;
}