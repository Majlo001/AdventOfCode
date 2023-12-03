#include <iostream>
#include <string>
#include <fstream>

#define fileName "input.txt"
#define testFileName "test.txt"

int analyzeLine(const std::string&);


int main() {
    std::string line;
    int sum = 0;

    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cout << "File not found!" << std::endl;
        return 1;
    }

    while (std::getline(file, line)) {
        sum += analyzeLine(line);
    }

    std::cout << "Result: " << sum << std::endl;
    file.close();
    return 0;
}





int analyzeLine(const std::string& line) {
    int result = 0;
    char num1, num2;

    for (auto it = line.begin(); it != line.end(); ++it) {
        if (*it >= '0' && *it <= '9') {
            num1 = *it;
            break;
        }
    }

    for (auto it = line.rbegin(); it != line.rend(); ++it) {
        if (*it >= '0' && *it <= '9') {
            num2 = *it;
            break;
        }
    }

    result = (num1 - '0') * 10 + (num2 - '0');
    return result;
}