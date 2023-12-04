#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>


#define fileName "input.txt"
#define testFileName "test.txt"

int analyzeLine(const std::string&);
std::vector<std::string> split(const std::string&, const char);

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



std::vector<std::string> split(const std::string& input, const char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(input);
    std::string part;

    while (std::getline(ss, part, delimiter)) {
        result.push_back(part);
    }

    return result;
}

int analyzeLine(const std::string& line) {
    int result = 1;
    std::vector<std::string> splited, splited_2, splited_3;
    std::map<std::string, int> colors = {{"red", 0}, {"green", 0}, {"blue", 0}};
    std::string part;

    splited = split(line, ':');
    part = splited[1];
    splited.clear();
    

    splited = split(part, ';');
    for (const auto& part_1 : splited) {
        splited_2 = split(part_1, ',');

        for (const auto& part_2 : splited_2) {
            splited_3 = split(part_2, ' ');

            if (colors.at(splited_3[2]) < std::stoi(splited_3[1])) {
                colors.at(splited_3[2]) = std::stoi(splited_3[1]);
            }

            splited_3.clear();
        }
        splited_2.clear();
    }
    splited.clear();

    for (const auto& color : colors) {
        result *= color.second;
    }

    return result;
}