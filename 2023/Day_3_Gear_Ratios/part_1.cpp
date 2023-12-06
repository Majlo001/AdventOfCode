#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>

#define fileName "input.txt"
#define testFileName "test.txt"


int analyzeLines(const std::string&, const std::string&, const std::string&);


int main() {
    std::string line, line1, line2, line3;
    int sum = 0;
    int lineNumber = 0;
    bool canContinue = true;

    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cout << "File not found!" << std::endl;
        return 1;
    }


    while (canContinue) {
        if (!file.eof()) 
            std::getline(file, line);
        else 
            canContinue = false;
        
        if (lineNumber == 0) {
            line1 = "";
            line2 = line;
            lineNumber++;
            continue;
        }
        
        line3 = line;
        if (!canContinue)
            line3 = "";

        sum += analyzeLines(line1, line2, line3);

        if (!canContinue)
            break;

        line1 = line2;
        line2 = line3;
        lineNumber++;
    }


    std::cout << "Result: " << sum << std::endl;
    file.close();
    return 0;
}


int analyzeLines(const std::string& line1, const std::string& line2, const std::string& line3) {
    int result = 0;
    int stringLength = line2.length();
    bool foundDigit = false, foundCharacter = false;
    std::vector<int> digits;

    for (int i = 0; i < stringLength; i++) {
        if(std::isdigit(line2[i])) {
            foundDigit = true;
            digits.push_back(line2[i] - '0');

            // Check up and down
            if (!foundCharacter) {
                if ((line1 != "" && !std::isdigit(line1[i]) && line1[i] != '.') 
                || (line3 != "" && !std::isdigit(line3[i]) && line3[i] != '.')) {
                    foundCharacter = true;
                }
            }

            // Check left
            if (!foundCharacter && digits.size() == 1 && i > 0) {
                if ((line1 != "" && !std::isdigit(line1[i-1]) && line1[i-1] != '.') 
                || (line3 != "" && !std::isdigit(line3[i-1]) && line3[i-1] != '.') || (!std::isdigit(line2[i-1]) && line2[i-1] != '.')) {
                    foundCharacter = true;
                }
            }

            // Check right
            if (!foundCharacter && digits.size() >= 1 && i < stringLength - 1) {
                if ((line1 != "" && !std::isdigit(line1[i+1]) && line1[i+1] != '.') 
                || (line3 != "" && !std::isdigit(line3[i+1]) && line3[i+1] != '.') || (!std::isdigit(line2[i+1]) && line2[i+1] != '.')) {
                    foundCharacter = true;
                }
            }
        }
        else {
            if (foundDigit && foundCharacter) {
                for (unsigned int i = 0; i < digits.size(); i++) {
                    result += digits[i] * std::pow(10, digits.size() - i - 1);
                }
            }

            digits.clear();
            foundDigit = false;
            foundCharacter = false;
        }
    }

    if (digits.size() > 0 && foundDigit && foundCharacter) {
        for (unsigned int i = 0; i < digits.size(); i++) {
            result += digits[i] * std::pow(10, digits.size() - i - 1);
        }

        digits.clear();
        foundDigit = false;
        foundCharacter = false;
    }


    return result;
}