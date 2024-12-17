#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

// Function to construct the frequency table for a given window
unordered_map<string, int> FrequencyTable(const string &window, int k) {
    unordered_map<string, int> freqMap;
    int n = window.length();
    for (int i = 0; i <= n - k; i++) {
        string pattern = window.substr(i, k);
        freqMap[pattern]++;
    }
    return freqMap;
}

void findClumps(const string &text, int k, int L, int t) {
    unordered_set<string> clumpKmers; // Store unique k-mers forming clumps
    int n = text.length();

    // Slide the window through the text
    for (int i = 0; i <= n - L; i++) {
        string window = text.substr(i, L);

        // Build frequency table for the current window
        unordered_map<string, int> freqMap = FrequencyTable(window, k);

        // Check for k-mers that meet or exceed the threshold t
        for (const auto &entry : freqMap) {
            if (entry.second >= t) {
                clumpKmers.insert(entry.first);
            }
        }
    }
    // Output the number of unique k-mers forming (L,t)-clumps
    cout << "Total number of unique 9-mers forming (500,3)-clumps: " << clumpKmers.size() << endl;

}

int main() {
    int k = 9;  // Length of the k-mer
    int L = 500;  // Window length
    int t = 3;  // Minimum number of occurrences within the window

    string fileName;
    cout << "Enter the filename containing the DNA sequence: ";
    cin >> fileName;

    // Open the file
    ifstream inputFile(fileName);
    if (!inputFile) {
        cerr << "Failed to open the file: " << fileName << endl;
        return 1;
    }

    // Read the DNA sequence from the file
    string text;
    string line;
    while (getline(inputFile, line)) {
        // Remove any whitespace
        line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
        text += line;
    }
    inputFile.close();

    // Convert text to uppercase
    transform(text.begin(), text.end(), text.begin(), ::toupper);

    // Validate the DNA sequence
    for (char nucleotide : text) {
        if (nucleotide != 'A' && nucleotide != 'C' && nucleotide != 'G' && nucleotide != 'T') {
            cerr << "Invalid nucleotide '" << nucleotide << "' in DNA sequence." << endl;
            return 1;
        }
    }

    findClumps(text, k, L, t);

    return 0;
}
