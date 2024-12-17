#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

int main() {
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
    std::string dnaSequence;
    std::string line;
    while (std::getline(inputFile, line)) {
        dnaSequence += line;
    }
    inputFile.close();

    int k = 9; // Length of k-mer
    int n = dnaSequence.length();
    if (n < k) {
        std::cout << "The DNA sequence is shorter than 9 nucleotides." << std::endl;
        return 0;
    }

    // Use an unordered_set to store unique 9-mers
    std::unordered_set<std::string> unique9mers;

    for (int i = 0; i <= n - k; ++i) {
        std::string kmer = dnaSequence.substr(i, k);
        unique9mers.insert(kmer);
    }

    // Output the number of unique 9-mers
    std::cout << "Total number of unique 9-mers: " << unique9mers.size() << std::endl;

    return 0;
}
