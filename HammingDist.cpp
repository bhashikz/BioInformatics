#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int hammingDist(const std::string &string1, const std::string &string2){

    int count = 0;

    for(size_t i = 0; i < string1.length(); i++){
        if(string1[i] != string2[i]){
            count++;
        }
    }
    return count;
}

int main(){

    string string1;
    std::cout << "Enter the first string: ";
    getline(cin, string1);

    string string2;
    std::cout << "Enter the second string: ";
    getline(cin, string2);

    int count = hammingDist(string1, string2);
    cout << "The Hamming distance between two strings " << count << endl;

    return 0;

}