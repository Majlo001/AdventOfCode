#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>


#define fileName "input.txt"
#define testFileName "test.txt"


template <typename T>
std::vector<T> split(const std::string&, const char, bool);
int analyzeLine(const std::string&, int*, int, int);


int main() {
    std::vector<std::string> lines;
    std::string line;
    int sum = 0, lineCount = 0;
    std::vector<int> copiesCount;

    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cout << "File not found!" << std::endl;
        return 1;
    }
    while (std::getline(file, line)) {
        lines.push_back(line);
        lineCount++;
    }

    int* cardCount = new int[lineCount];
    for (int i = 0; i < lineCount; ++i)
        cardCount[i] = 1;


    for (int i = 0; i < lineCount; i++) 
        analyzeLine(lines[i], cardCount, lineCount, i);

    for (int i = 0; i < lineCount; i++)
        sum += cardCount[i];

    std::cout << "Result: " << sum << std::endl;
    delete[] cardCount;
    file.close();
    return 0;
}


template <typename T>
std::vector<T> split(const std::string& input, const char delimiter, bool reduceEmptySpaces = false) {
    std::vector<T> result;
    std::stringstream ss(input);
    std::string part;

    while (std::getline(ss, part, delimiter)) {
        if (reduceEmptySpaces && part == "")
            continue;
        if constexpr (std::is_same_v<T, int>)
            result.push_back(std::stoi(part));
        else
            result.push_back(part);
    }

    return result;
}


int analyzeLine(const std::string& line, int* cardCount, int lineCount, int index) {
    std::vector<std::string> splited;
    std::vector<int> splitedPart1, splitedPart2;
    std::string part;
    int result = 0;
    int copiesCount = 0;


    splited = split<std::string>(line, ':');
    part = splited[1];
    splited.clear();
    

    splited = split<std::string>(part, '|');
    splitedPart1 = split<int>(splited[0], ' ', true);
    splitedPart2 = split<int>(splited[1], ' ', true);
    splited.clear();

    for (int i = 0; i < splitedPart1.size(); i++)
        for (int j = 0; j < splitedPart2.size(); j++)
            if (splitedPart1[i] == splitedPart2[j])
                copiesCount++;
    
    if (copiesCount > 0){ 
        for (int i = 0; i < copiesCount; i++) {
            cardCount[index + i + 1] += cardCount[index];
        }
    }

    return result;
}