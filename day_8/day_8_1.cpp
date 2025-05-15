#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

using namespace std;


struct Node {
    string label;
    string left;
    string right;
};

string getLeft(string line) {
    return line.substr(7, 3);
}

string getRight(string line) {
    return line.substr(12, 3);
}

Node parseNode(string line) {
    string label = line.substr(0, 3);
    string left = getLeft(line);
    string right = getRight(line);
    return Node{label, left, right};
}

int traverseRoute(string instructions, vector<Node> nodes) {
    while ()
    return 0;
}

int solveRiddle() {
    int solution = 0;
    string line;
    ifstream file ("input.txt");
    if (file.is_open()) {
        getline(file, line);
        string instructions = line;
        getline(file, line);
        vector<Node> nodes;
        while (getline(file, line)) {
            nodes.push_back(parseNode(line));
        }
        solution = traverseRoute(instructions, nodes);
        file.close();
    } else {
        cout << "Unable to open file" << endl;
    }
}

int main() {
    int solution = solveRiddle();
    cout << solution << endl;
    return 0;
}