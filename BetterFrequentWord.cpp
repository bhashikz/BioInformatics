#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

// Frequency table construction
unordered_map<string, int> FrequencyTable(const std::string &text, const int k){

    unordered_map<string, int> freqMap;
    int n;
    n = text.length();
    for(int i = 0; i <= (n - k); i++){
        string pattern = text.substr(i,k); 
        freqMap[pattern] = freqMap[pattern] + 1;
    }
    return freqMap;
}

// Return maximum value from the freqMap Table
int MaxMap(unordered_map<string, int> freqMap) {
    int max = 0;

    // Iterate through the map with a range-based for loop
    for (const pair<string, int>& entry : freqMap) {
        if (entry.second > max) {  // entry.second is the frequency
            max = entry.second;
        }
    }
    return max;
}

int BetterFrequentWords(const std::string &text, const int k){
    unordered_map<string, int> freqMap = FrequencyTable(text, k);
    
    vector<string> FrequentPatterns;
    int max = MaxMap(freqMap);

    // Find all patterns that occur with the maximum frequency
    for (const auto& pair : freqMap) {
        if (pair.second == max) {
            FrequentPatterns.push_back(pair.first);  // Add pattern to result
        }
    }
    // Print the most frequent patterns
    cout << "Most frequent patterns are: " << endl;
    for (const string &pattern : FrequentPatterns) {
        cout << pattern << " ";
    }
    cout << endl;

    return 0;
}

int main(){
    string text;
    std::cout << "Enter the text: ";
    getline(cin, text);

    int k;
    std::cout << "Enter the length of the pattern, k : ";
    std::cin >> k;

    // Call BetterFrequentWords to get the most frequent patterns
    BetterFrequentWords(text, k);

    return 0;
}