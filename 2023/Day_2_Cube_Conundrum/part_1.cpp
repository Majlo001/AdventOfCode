#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>


#define fileName "input.txt"
#define testFileName "test.txt"

bool analyzeLine(const std::string&, const std::map<std::string, int>&);

int main() {
    std::string line;
    int sum = 0, i = 0;
    std::map<std::string, int> colors = {{"red", 12}, {"green", 13}, {"blue", 14}};

    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cout << "File not found!" << std::endl;
        return 1;
    }

    while (std::getline(file, line)) {
        i++;
        if(analyzeLine(line, colors))
            sum += i;
    }

    std::cout << "Result: " << sum << std::endl;
    file.close();
    return 0;
}



std::vector<std::string> split(const std::string& input, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(input);
    std::string part;

    while (std::getline(ss, part, delimiter)) {
        result.push_back(part);
    }

    return result;
}

bool analyzeLine(const std::string& line, const std::map<std::string, int>& colors) {
    std::vector<std::string> splited, splited_2, splited_3;
    std::string part;

    splited = split(line, ':');
    part = splited[1];
    splited.clear();
    

    splited = split(part, ';');
    for (const auto& part_1 : splited) {
        splited_2 = split(part_1, ',');

        for (const auto& part_2 : splited_2) {
            splited_3 = split(part_2, ' ');

            if (std::stoi(splited_3[1]) > colors.at(splited_3[2])) {
                return false;
            }
            splited_3.clear();
        }
        splited_2.clear();
    }
    splited.clear();

    return true;
}