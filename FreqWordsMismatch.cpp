#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

void generateNeighbors(string pattern, int d, size_t pos, unordered_set<string> &neighbors, const string &alphabet = "ACGT") {
    if (d == 0 || pos >= pattern.length()) {
        neighbors.insert(pattern);
        return;
    }

    // Keep the current character unchanged
    generateNeighbors(pattern, d, pos + 1, neighbors, alphabet);

    // Generate mismatches
    char originalChar = pattern[pos];
    for (char c : alphabet) {
        if (c != originalChar) {
            pattern[pos] = c;
            generateNeighbors(pattern, d - 1, pos + 1, neighbors, alphabet);
            pattern[pos] = originalChar; // Restore original character
        }
    }
}

// Function to build the frequency table
unordered_map<string, int> FrequencyTable(const string &text, int k, int d) {
    unordered_map<string, int> freqMap;
    int n = text.length();

    for (int i = 0; i <= n - k; i++) {
        string pattern = text.substr(i, k);
        unordered_set<string> neighbors;

        // Generate all possible patterns with up to `d` mismatches
        generateNeighbors(pattern, d, 0, neighbors);

        // Count each unique neighbor in the frequency map
        for (const string &neighbor : neighbors) {
            freqMap[neighbor]++;
        }
    }

    return freqMap;
}

// Return maximum value from the freqMap Table
int MaxMap(unordered_map<string, int> &freqMap) {
    int max = 0;

    // Iterate through the map with a range-based for loop
    for (const pair<string, int>& entry : freqMap) {
        if (entry.second > max) {  // entry.second is the frequency
            max = entry.second;
        }
    }
    return max;
}

int FrequentWordsMismatches(const std::string &text, const int k, const int d){
    unordered_map<string, int> freqMap = FrequencyTable(text, k, d);
    
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

    int d;
    std::cout << "Enter the number of mismatches allowed : ";
    std::cin >> d;

    FrequentWordsMismatches(text, k, d);

    return 0;
}
