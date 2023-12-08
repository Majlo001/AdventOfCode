#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

class Node {
private:
    std::string name;
    std::string n1, n2;

public:
    Node(const std::string& line);

    std::string getName() const;
    std::string getN1() const;
    std::string getN2() const;
};

template <typename T>
std::vector<T> split(const std::string& input, const char delimiter, bool reduceEmptySpaces = false) {
    std::vector<T> result;
    std::stringstream ss(input);
    std::string part;

    while (std::getline(ss, part, delimiter)) {
        if (reduceEmptySpaces && part == "")
            continue;
        if constexpr (std::is_same_v<T, int>)
            result.push_back(std::stoll(part));
        else
            result.push_back(part);
    }

    return result;
}

Node* findNode(const std::vector<Node*>& nodes, const std::string& name);

void removeChar(std::string& str, char ch);

#endif // NODE_H
