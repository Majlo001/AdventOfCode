#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <climits>
#include <omp.h>


#define fileName "input.txt"
#define testFileName "test.txt"


template <typename T>
std::vector<T> split(const std::string&, const char, bool=false);

std::vector<long long> analyzeFirstLine(const std::string&);


class CategoryMap {
private:
    struct CorrespondingNumbers {
        long long n1, n2, range;
    };
public:
    std::string category1, category2;
    std::vector<CorrespondingNumbers> correspondingNumbers;

    CategoryMap(std::string& line) {
        std::vector<std::string> splited;
        splited = split<std::string>(line, ' ');
        splited = split<std::string>(splited[0], '-');

        this->category1 = splited[0];
        this->category2 = splited[2];
    }

    ~CategoryMap() {
        for (unsigned int i = 0; i < correspondingNumbers.size(); i++)
            correspondingNumbers.pop_back();
    }
    
    void processLines(std::vector<std::string>& lines) {
        std::vector<long long> splited;

        for (unsigned int i = 0; i < lines.size(); i++) {
            splited = split<long long>(lines[i], ' ', true);
            CorrespondingNumbers cn;
            cn.n1 = splited[1];
            cn.n2 = splited[0];
            cn.range = splited[2];
            correspondingNumbers.push_back(cn);
        }
    }

    long long getCorrespondingNumber(long long number) {
        for (unsigned int i = 0; i < correspondingNumbers.size(); i++) {
            if (correspondingNumbers[i].n1 <= number && number <= correspondingNumbers[i].n1 + correspondingNumbers[i].range) {
                long long ret = number - correspondingNumbers[i].n1;
                ret = correspondingNumbers[i].n2 + ret;
                return ret;
            }
        }
        return number;
    }

};

int main() {
    std::string line;
    long long min = LLONG_MAX;
    std::vector<long long> seeds;
    std::vector<std::string> lines;
    std::vector<CategoryMap*> categoryMaps;

    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cout << "File not found!" << std::endl;
        return 1;
    }

    std::getline(file, line);
    seeds = analyzeFirstLine(line);

    CategoryMap* cm;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            char firstChar = line[0];

            if (!isdigit(firstChar)) {
                cm = new CategoryMap(line);
                categoryMaps.push_back(cm);
            }
            else {
                lines.push_back(line);
            }
        }
        else {
            if (!lines.empty())
                cm->processLines(lines);
            lines.clear();
        }
    }
    if (!lines.empty()) {
        cm->processLines(lines);
        lines.clear();
    }

    long long temp = 0;
    std::cout << "seeds size: " << seeds.size() << std::endl;
    
    int max_threads = omp_get_max_threads();
    omp_set_num_threads(max_threads);

#pragma omp parallel for private(temp) shared(min)
    for (int s = 0; s < seeds.size(); s+=2) {
        for (long long i = seeds[s]; i < (seeds[s] + seeds[s+1]); i++) {
            std::string category = "seed";
            temp = i;

            for (unsigned int j = 0; j < categoryMaps.size(); j++) {
                if (categoryMaps[j]->category1 == category) {
                    temp = categoryMaps[j]->getCorrespondingNumber(temp);
                }
                category = categoryMaps[j]->category2;
            }
            if (temp < min)
                min = temp;
        }
        std::cout << s << " " << min << " " << temp << std::endl;
    }

    std::cout << "Result: " << min << std::endl;
    file.close();
    for (unsigned int i = 0; i < categoryMaps.size(); i++)
        delete categoryMaps[i];

    return 0;
}


template <typename T>
std::vector<T> split(const std::string& input, const char delimiter, bool reduceEmptySpaces) {
    std::vector<T> result;
    std::stringstream ss(input);
    std::string part;

    while (std::getline(ss, part, delimiter)) {
        if (reduceEmptySpaces && part == "")
            continue;
        if constexpr (std::is_same_v<T, long long>)
            result.push_back(std::stoll(part));
        else
            result.push_back(part);
    }

    return result;
}


std::vector<long long> analyzeFirstLine(const std::string& line) {
    std::vector<long long> result;
    std::vector<std::string> splited;
    std::string part;

    splited = split<std::string>(line, ':', true);
    part = splited[1];
    splited.clear();
    result = split<long long>(part, ' ', true);

    return result;
}