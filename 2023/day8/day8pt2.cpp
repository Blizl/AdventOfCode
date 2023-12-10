#include <iostream>
#include "../utils.h"
#include <unordered_map>
#include <queue>
#include <numeric>
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
    vector<string> starts;
    for (int i = 0; i < lines.size(); i++) {
        if (i < 2)  {
            continue;
        }
        string key = parseKey(lines[i]);
        if (key[key.length() -1] == 'A') {
            starts.push_back(key);
        }
        pair<string, string> value = parseValue(lines[i]);
        map[key] = value;
    }
    cout << "starts are " << starts << endl;

    // parse to map
    vector<int> stepsVector;
    for (auto start : starts) {
        queue<char> q;
        string current = start;
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
            if (current[current.length() -1] == 'Z') {
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
        stepsVector.push_back(steps);

    }
    cout << "stepsvector is " << stepsVector << endl;
    long result = stepsVector[0];  // Initialize result with first value
    for (size_t i = 1; i < stepsVector.size(); ++i) {
        result = lcm(result, stepsVector[i]);
    }

    cout << "sum is " << result << endl;
    return 0;
}