#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

// Function to calculate Hamming distance between two strings
int hammingDist(const string &s1, const string &s2) {
    if (s1.length() != s2.length()) {
        throw std::invalid_argument("Strings must be of equal length");
    }
    int count = 0;
    for (size_t j = 0; j < s1.length(); j++) {
        if (s1[j] != s2[j]) {
            count++;
        }
    }
    return count;
}

// Neighbors function implemented according to the pseudocode
unordered_set<string> Neighbors(const string &pattern, int d, const string &alphabet = "ACGT") {
    unordered_set<string> neighborhood;

    if (d == 0) {
        neighborhood.insert(pattern);
        return neighborhood;
    }
    if (pattern.length() == 1) {
        for (char c : alphabet) {
            string neighbor(1, c);
            neighborhood.insert(neighbor);
        }
        return neighborhood;
    }

    // Recursive call on the suffix of the pattern
    string suffix = pattern.substr(1);
    unordered_set<string> suffixNeighbors = Neighbors(suffix, d, alphabet);

    for (const string &text : suffixNeighbors) {
        int hd = hammingDist(suffix, text);
        if (hd < d) {
            // Prepend each nucleotide to text
            for (char x : alphabet) {
                string neighbor = x + text;
                neighborhood.insert(neighbor);
            }
        } else {
            // Prepend the first symbol of the pattern
            string neighbor = pattern[0] + text;
            neighborhood.insert(neighbor);
        }
    }
    return neighborhood;
}

// Function to find the maximum value in the frequency map
int MaxMap(const unordered_map<string, int> &freqMap) {
    int max = 0;

    // Iterate through the map
    for (const auto &entry : freqMap) {
        if (entry.second > max) {
            max = entry.second;
        }
    }
    return max;
}

string ReverseComplement(const string &pattern) {
    string complement;
    for (char nucleotide : pattern) {
        switch (nucleotide) {
            case 'A': complement += 'T'; break;
            case 'T': complement += 'A'; break;
            case 'C': complement += 'G'; break;
            case 'G': complement += 'C'; break;
        }
    }
    reverse(complement.begin(), complement.end());
    return complement;
}

vector<string> FreqWordsMismatchRevComp(const string &text, int k, int d) {
    unordered_map<string, int> freqMap;
    int n = text.length();

    // Iterate over all k-mers in the text
    for (int i = 0; i <= n - k; i++) {
        string pattern = text.substr(i, k);
        unordered_set<string> neighborhood = Neighbors(pattern, d);

        // Update frequency map for each neighbor and its reverse complement
        for (const string &neighbor : neighborhood) {
            freqMap[neighbor]++;
            string reverseComplement = ReverseComplement(neighbor);
            freqMap[reverseComplement]++;
        }
    }
    // Find the maximum frequency
    int maxFreq = MaxMap(freqMap);

    // Identify patterns with the maximum frequency
    vector<string> Patterns;
    for (const auto &pair : freqMap) {
        if (pair.second == maxFreq) {
            Patterns.push_back(pair.first);
        }
    }
    return Patterns;
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

    vector<string> frequentPatterns = FreqWordsMismatchRevComp(text, k, d);

    // Print the most frequent patterns
    cout << "Most frequent patterns with up to " << d << " mismatches are: " << endl;
    for (const string &pattern : frequentPatterns) {
        cout << pattern << " ";
    }
    cout << endl;

    return 0;
}