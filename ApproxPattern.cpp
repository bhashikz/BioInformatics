#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

int hammingDist(const string &DnaPattern, const string &pattern){

    int count = 0;

    for(size_t j = 0; j < pattern.length(); j++){
        if(DnaPattern[j] != pattern[j]){
            count++;
        }
    }
    return count;
}

vector<int> findStartingPositions(const string& pattern, const string& text, const int d) {
    size_t textLen = text.length();
    size_t patternLen = pattern.length();
    
    vector<int> positions;

    for (size_t i = 0; i <= textLen - patternLen; i++){
        string DnaPattern = text.substr(i, patternLen);

        int count = hammingDist(DnaPattern, pattern);

        if (count <= d){
            positions.push_back(i);
        }
    }
    return positions;
}

int main(){    
    
    string pattern;
    std::cout << "Enter the pattern: ";
    getline(cin, pattern);

    int d;
    std::cout << "Enter the number of mismatches allowed : ";
    std::cin >> d;

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

    vector<int> positions = findStartingPositions(pattern, text, d);

    cout << "Starting positions of the pattern with at most " << d << " mismatches: ";
    for (int pos : positions) {
        cout << pos << " ";
    }
    cout << endl;

    // Output the number of positions
    cout << "Number of positions: " << positions.size() << endl;

    return 0;


}
