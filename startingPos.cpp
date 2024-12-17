#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<int> findStartingPositions(const string& pattern, const string& text) {
    size_t textLen = text.length();
    size_t patternLen = pattern.length();
    
    vector<int> positions;

    for (size_t i = 0; i <= textLen - patternLen; i++) {
        if (text.substr(i, patternLen) == pattern) {
            positions.push_back(i);
        }
    }
    return positions;
}

int main() {
    // Input the pattern manually
    string pattern;
    cout << "Enter the pattern: ";
    getline(cin, pattern);

    // Read the text from a file
    string filename;
    cout << "Enter the filename containing the text: ";
    getline(cin, filename);

    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    // Read the entire file content as text
    string text;
    string line;
    while (getline(file, line)) {
        text += line;
    }
    file.close();

    vector<int> positions = findStartingPositions(pattern, text);

    if (positions.empty()) {
        cout << "Pattern not found in the text." << endl;
    } else {
        cout << "The starting positions of the pattern are: ";
        for (const int& position : positions) {
            cout << position << " ";
        }
        cout << endl;
    }

    return 0;
}
