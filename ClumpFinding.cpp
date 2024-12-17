#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

unordered_map<string, int> FrequencyTable(const std::string &window, const int k){

    unordered_map<string, int> freqMap;
    int n;
    n = window.length();
    for(int i = 0; i <= (n - k); i++){
        string pattern = window.substr(i,k); 
        freqMap[pattern] = freqMap[pattern] + 1;
    }
    return freqMap;
}

int findClumps(const std::string &text, const int k, const int L, const int t){
    unordered_map<string, int> freqMap;
    unordered_set<string> FrequentPatterns;

    int n = text.length();

    for(int i = 0; i <= (n - L); i++){ 
        string window = text.substr(i, L); 
        freqMap = FrequencyTable(window, k);

        // Iterate through the map with a range-based for loop
        for (const pair<string, int> &entry : freqMap){
            if (entry.second >= t){ // entry.second is the frequency
                FrequentPatterns.insert(entry.first);
            }
        }
        freqMap.clear(); // Clear freqMap for the next window
    }

    // Print the most frequent patterns
    cout << "Most frequent patterns are: " << endl;
    for (const string &pattern : FrequentPatterns) {
        cout << pattern << " ";
    }
    cout << endl;

    return 0;
}

int main() {
    int k;
    std::cout << "Enter the length of the pattern, k : ";
    std::cin >> k;

    int L;
    std::cout << "Enter the length of the window, L : ";
    std::cin >> L;

    int t;
    std::cout << "Enter the number of times the pattern should occur : ";
    std::cin >> t;

    std::string text;
    std::string fileName;

    std::cout << "Enter the filename containing the DNA sequence: ";
    std::cin >> fileName;

    // Open the file
    std::ifstream inputFile(fileName);
    if (!inputFile) {
        std::cerr << "Failed to open the file: " << fileName << std::endl;
        return 1;
    }

    // Read the DNA sequence from the file
    text.assign((std::istreambuf_iterator<char>(inputFile)),
                        std::istreambuf_iterator<char>());

    inputFile.close();

    findClumps(text, k, L, t);

    return 0;
}