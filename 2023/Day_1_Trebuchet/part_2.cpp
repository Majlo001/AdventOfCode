#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

#define fileName "input.txt"
#define testFileName "test2.txt"

int analyzeLine(const std::string&, const std::map<std::string, int>&);
std::vector<int> checkWord(const std::string&, const std::map<std::string, int>&);


int main() {
    std::string line;
    int sum = 0;
    std::map<std::string, int> numWords = { {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9} };

    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cout << "File not found!" << std::endl;
        return 1;
    }

    while (std::getline(file, line)) {
        sum += analyzeLine(line, numWords);
    }

    std::cout << "Result: " << sum << std::endl;
    file.close();
    return 0;
}


std::vector<int> checkWord(const std::string& word, const std::map<std::string, int>& numWords) {
    std::vector<int> foundKeywords;

    for (size_t i = 0; i < word.length(); ++i) {
        for (const auto& entry : numWords) {
            const std::string& keyword = entry.first;

            if (word.compare(i, keyword.length(), keyword) == 0) {
                foundKeywords.push_back(entry.second);
                break;
            }
        }
    }

    return foundKeywords;
}

int analyzeLine(const std::string& line, const std::map<std::string, int>& numWords) {
    std::vector<int> digits, numFromWord;
    std::string word;
    int result = 0;

    for (char chr : line) {
        if (std::isdigit(chr)) {
            numFromWord = checkWord(word, numWords);
            if (!numFromWord.empty()) {
                for (int num : numFromWord) {
                    digits.push_back(num);
                }
                word.clear();
            }

            digits.push_back(chr - '0');
        }
        else if (std::isalpha(chr)) {
            word += chr;
        }
    }

    if (!word.empty()) {
        numFromWord = checkWord(word, numWords);
        if (!numFromWord.empty()) {
            for (int num : numFromWord) {
                digits.push_back(num);
            }
        }
    }

    result = digits.front() * 10 + digits.back();
    return result;
}