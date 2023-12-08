#include "Node.h"
#include <sstream>



Node::Node(const std::string& line) {
    std::vector<std::string> splited = split<std::string>(line, '=');
    removeChar(splited[0], ' ');
    this->name = splited[0];

    removeChar(splited[1], ')');
    removeChar(splited[1], '(');
    removeChar(splited[1], ' ');
    splited = split<std::string>(splited[1], ',');
    this->n1 = splited[0];
    this->n2 = splited[1];
}

std::string Node::getName() const {
    return this->name;
}

std::string Node::getN1() const {
    return this->n1;
}

std::string Node::getN2() const {
    return this->n2;
}

Node* findNode(const std::vector<Node*>& nodes, const std::string& name) {
    for (auto node : nodes)
        if (node->getName() == name)
            return node;

    return nullptr;
}

void removeChar(std::string& str, char ch) {
    str.erase(std::remove(str.begin(), str.end(), ch), str.end());
}
