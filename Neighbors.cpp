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

int main(){
    string pattern;
    std::cout << "Enter the pattern: ";
    getline(cin, pattern);

    int d;
    std::cout << "Enter the number of mismatches allowed : ";
    std::cin >> d;

    // Get the neighbors
    unordered_set<string> neighbors = Neighbors(pattern, d);

    // Print the neighbors
    cout << "Neighbors of pattern \"" << pattern << "\" with d = " << d << " are:" << endl;
    for (const string &neighbor : neighbors) {
        cout << neighbor << endl;
    }

    return 0;
}