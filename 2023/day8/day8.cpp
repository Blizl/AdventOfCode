#include <iostream>
#include "../utils.h"
#include <unordered_map>
#include <queue>

// struct Node {
//     Node* left;
//     Node* right;
//     string value;
//     Node(Node* left, Node* right, string value)
//         : left(left), right(right), value(value){}
// };
string parseKey(string line) { 
    int spaceIndex = line.find_first_of(' ');
    return line.substr(0, spaceIndex);
}

pair<string, string> parseValue(string line) {
    int equalsIndex = line.find_first_of('=');
    string lineWithoutKey = line.substr(equalsIndex +1, line.length());
    int commaIndex = lineWithoutKey.find_first_of(',');
    string firstValue = lineWithoutKey.substr(2, commaIndex-2);
    string secondValue = lineWithoutKey.substr(
        commaIndex + 2, lineWithoutKey.length() - commaIndex - 3);
    return make_pair(firstValue, secondValue);
}

int main() {
    vector<string> lines = readLines("input.txt");
    unordered_map<string, pair<string, string> > map;
    string instructions = lines[0];
    string starting = "AAA";
    for (int i = 0; i < lines.size(); i++) {
        if (i < 2)  {
            continue;
        }
        string key = parseKey(lines[i]);
        // if (i == 2) {
        //     starting = key;
        // }
        // cout << "key is " << key << endl;
        pair<string, string> value = parseValue(lines[i]);
        map[key] = value;
    }

    // parse to map

    queue<char> q;
    string current = starting;
    cout << "number of instructions is " << instructions.length() << endl;
    for (auto c : instructions) {
        q.push(c);
    }
    int steps = 0;
    string target = "ZZZ";
    while (!q.empty()) {
        char direction = q.front();
        pair<string, string> current_pair = map[current];
        if (direction == 'L') {
            current = current_pair.first;
        } else {
            current = current_pair.second;
        }
        steps++;
        cout << "current is " << current << endl;
        if (current == target) {
            break;
        }
        q.pop();
        if (q.empty()) {
            for (auto c : instructions) {
                q.push(c);
            }
        }
    }
    cout << "Number of steps is " << steps << endl;

    return 0;
}