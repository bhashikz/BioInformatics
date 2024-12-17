#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

int FindMin(const std::string &text){

    vector<int> skew(text.length() + 1, 0); // Initialize skew vector with size n+1, all zeros
    int n = text.length();

    for(int i = 0; i < n; i++){
        if(text[i] == 'G'){
            skew[i+1] = skew[i] + 1;
        }
        else if(text[i] == 'C'){
            skew[i+1] = skew[i] - 1;
        }
        else 
            skew[i+1] = skew[i];
    }
    
    // Find the minimum skew value
    // int minSkew = *min_element(skew.begin(), skew.end());

    int minSkew = skew[0];
    for(int val : skew){
        if(val < minSkew){
            minSkew = val;
        }
    }

    // Print all positions with the minimum skew value
    cout << "Positions with minimum skew: ";
    for (int i = 0; i < skew.size(); i++) {
        if (skew[i] == minSkew) {
            cout << i << " ";
        }
    }
    cout << endl;

    return minSkew;

}

int main(){    

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

    // Find the minimum skew
    int minSkew = FindMin(text);
    cout << "Minimum skew value: " << minSkew << endl;

    return 0;

}