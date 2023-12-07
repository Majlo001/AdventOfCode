#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>


#define fileName "input.txt"
#define testFileName "test.txt"


template <typename T>
std::vector<T> split(const std::string&, const char, bool);
int analyzeLine(const std::string&);


int main() {
    std::string line;
    int sum = 0, i = 0;

    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cout << "File not found!" << std::endl;
        return 1;
    }

    while (std::getline(file, line))
        sum += analyzeLine(line);

    std::cout << "Result: " << sum << std::endl;
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


int analyzeLine(const std::string& line) {
    std::vector<std::string> splited;
    std::vector<int> splitedPart1, splitedPart2;
    std::string part;
    unsigned int result;
    int wpCount = 0;

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
                wpCount++;
    
    if (wpCount == 0)
        return 0;
    
    result = 1;
    wpCount = wpCount -1;
    result = result << wpCount;

    return result;
}