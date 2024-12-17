#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_map>

std::string getReverseComplement(const std::string& sequence) {
    // Mapping of nucleotides to their complements
    std::unordered_map<char, char> complement = {
        {'A', 'T'},
        {'T', 'A'},
        {'C', 'G'},
        {'G', 'C'},
        {'a', 't'},
        {'t', 'a'},
        {'c', 'g'},
        {'g', 'c'}
    };

std::string reverseComplement;

// Generate the complement and reverse it
for (int i = sequence.length() - 1; i >= 0; --i) {
    char base = sequence[i];
    if (base == '\n' || base == '\r') {
        // Skip newline characters
        continue;
    }
    if (complement.find(base) != complement.end()) {
        reverseComplement += complement[base];
    } else {
        // Handle invalid characters
        std::cerr << "Invalid nucleotide found: " << base << std::endl;
        return "";
    }
}
return reverseComplement;
}

int main() {
    std::string dnaSequence;
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
    dnaSequence.assign((std::istreambuf_iterator<char>(inputFile)),
                        std::istreambuf_iterator<char>());

    inputFile.close();

    std::string reverseComplement = getReverseComplement(dnaSequence);

    if (!reverseComplement.empty()) {
        std::cout << "Reverse Complement: " << reverseComplement << std::endl;
    } else {
        std::cerr << "Failed to compute reverse complement due to invalid input." << std::endl;
    }

    return 0;
}
