#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "../utils.h"
using namespace std;


vector<int> gameSetToVector(vector<string> gameSet) {
    vector<int> gameSetVector = {0, 0, 0};
    for (int i = 0; i < gameSet.size() - 1; i++) {
        removeAllOccurrences(gameSet[i+1], ',');
        if (gameSet[i + 1] == "red") {
            // cout << "is red, setting to " << gameSet[i] << endl;
            gameSetVector[0] = stoi(gameSet[i]);
        } else if (gameSet[i + 1] == "green") {
            // cout << "is green, setting to " << gameSet[i] << endl;
            gameSetVector[1] = stoi(gameSet[i]);
        } else if (gameSet[i + 1] == "blue") {
            // cout << "is blue, setting to " << gameSet[i] << endl;
            gameSetVector[2] = stoi(gameSet[i]);
        }
    }

    return gameSetVector;
}
bool allValid(vector<string> tokens, vector<int> config) {
    // [[3,4,0], []]
    vector<vector<int>> cubes;
    for (auto token : tokens) {
        token = lstrip(token);
        auto gameSet = splitString(token, ' ');
        vector<int> cubesVector = gameSetToVector(gameSet);
        for (int i = 0; i < config.size(); i++) {
            if (config[i] < cubesVector[i]) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    std::ifstream inputFile("input.txt");
    std::string line;
    // red, green, blue
    vector<int> config = {12, 13, 14};
    int currentSum = 0;

    while (std::getline(inputFile, line)) {
        // Process each line as needed
        
        // 5 because game + space is 5 characters
        int id = stoi(line.substr(5, line.find(":") +1));
        string parsedLine =
            line.substr(line.find(":") + 2, line.length() - line.find(":"));
        vector<string> tokens = splitString(parsedLine, ';');
        if (allValid(tokens, config)) {
            currentSum += id;
        }


    }
    cout << "res is " << currentSum << endl;

    return 0;
}