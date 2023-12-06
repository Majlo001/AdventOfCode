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
int findDigits(const std::string&, int, int);


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


int findDigits(const std::string& line, int index, int direction) {
    std::vector<int> digits;
    int result = 0;
    
    if (direction == -1) {
        for (int i = index; i >= 0; i--) {
            if (std::isdigit(line[i])) 
                digits.insert(digits.begin(), line[i] - '0');
            else
                break;
        }
    }
    else if (direction == 1) {
        for (unsigned int i = index; i < line.length(); i++) {
            if (std::isdigit(line[i]))
                digits.push_back(line[i] - '0');
            else
                break;
        }
    }
    else {
        for (int i = index; i >= 0; i--) {
            if (std::isdigit(line[i])) 
                digits.insert(digits.begin(), line[i] - '0');
            else
                break;
        }
        for (unsigned int i = index + 1; i < line.length(); i++) {
            if (std::isdigit(line[i]))
                digits.push_back(line[i] - '0');
            else
                break;
        }
    }

    for (unsigned int i = 0; i < digits.size(); i++) {
        result += digits[i] * std::pow(10, digits.size() - i - 1);
    }
    
    return result;
}


int analyzeLines(const std::string& line1, const std::string& line2, const std::string& line3) {
    int result = 0;
    int stringLength = line2.length();
    std::vector<int> digits;

    for (int i = 0; i < stringLength; i++) {
        if(line2[i] == '*') {
            std::vector<int> gearDigits;
            bool foundUp = false, foundDown = false;
            
            // left side       
            if (i > 0 && std::isdigit(line2[i - 1]))
                gearDigits.push_back(findDigits(line2, i - 1, -1));

            // right side
            if (i < stringLength - 1 && std::isdigit(line2[i + 1]))
                gearDigits.push_back(findDigits(line2, i + 1, 1));

            // up side
            if (line1 != "" && std::isdigit(line1[i])) {
                gearDigits.push_back(findDigits(line1, i, 0));
                foundUp = true;
            }

            // down side
            if (line3 != "" && std::isdigit(line3[i])) {
                gearDigits.push_back(findDigits(line3, i, 0));
                foundDown = true;
            }
                

            // check diagonals
            if (gearDigits.size() < 2) {
                if (line1 != "" && !foundUp && i > 0 && std::isdigit(line1[i - 1]))
                    gearDigits.push_back(findDigits(line1, i-1, 0));

                if (line1 != "" && !foundUp && i < stringLength - 1 && std::isdigit(line1[i + 1]))
                    gearDigits.push_back(findDigits(line1, i+1, 0));

                if (line3 != "" && !foundDown &&  i > 0 && std::isdigit(line3[i - 1]))
                    gearDigits.push_back(findDigits(line3, i-1, 0));

                if (line3 != "" && !foundDown &&  i < stringLength - 1 && std::isdigit(line3[i + 1]))
                    gearDigits.push_back(findDigits(line3, i+1, 0));
            }


            if (gearDigits.size() == 2) {
                int ratio = 1;
                for (unsigned int i = 0; i < gearDigits.size(); i++)
                    ratio *= gearDigits[i];
                
                result += ratio;
            }
        }
    }


    return result;
}