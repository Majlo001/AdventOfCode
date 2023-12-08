#include "Node.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>


#define fileName "input.txt"
#define testFileName "test.txt"


int main() {
    std::string line, firstLine;
    int steps = 0;
    std::vector<Node*> nodes;

    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cout << "File not found!" << std::endl;
        return 1;
    }

    std::getline(file, firstLine);
    while(std::getline(file, line)) {
        if (line == "" || line == "\n")
            continue;

        Node* node = new Node(line);
        nodes.push_back(node);
    }

    Node* tmpNonde = findNode(nodes, "AAA");
    bool isFound = false;
    while(!isFound)
        for (int i = 0; i < firstLine.length(); i++) {
            steps++;

            if (firstLine[i] == 'L')
                tmpNonde = findNode(nodes, tmpNonde->getN1());
            else if (firstLine[i] == 'R')
                tmpNonde = findNode(nodes, tmpNonde->getN2());

            if (tmpNonde->getName() == "ZZZ") {
                isFound = true;
                break;
            }

        }

    std::cout << "Result: " << steps << std::endl;
    file.close();

    for (Node* node : nodes)
        delete node;

    return 0;
}