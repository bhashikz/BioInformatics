#include <iostream>
#include <string>

using namespace std;

int patternCount(const std::string &text, const std::string &pattern){
    int count = 0;
    size_t textLen = text.length();
    size_t patternLen = pattern.length();
    
    for (int i = 0; i <= (textLen - patternLen); i++){
        if(text.substr(i, patternLen) == pattern){
            count = count + 1;
        }
    }
    return count;
}

int main(){

    string text;
    std::cout << "Enter the text: ";
    getline(cin, text);

    string pattern;
    std::cout << "Enter the pattern: ";
    getline(cin, pattern);

    int result = patternCount(text, pattern);
    std::cout << "The pattern '" << pattern << "' appears " << result << " times in the text." << std::endl;

}