#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "../utils.h"
using namespace std;

vector<int> gameToVector(vector<string> game) {
    vector<int> gameSetVector = {0, 0, 0};
    for (int i = 0; i < game.size() - 1; i++) {
        removeAll(game[i + 1], ',');
        if (game[i + 1] == "red") {
            gameSetVector[0] = stoi(game[i]);
        } else if (game[i + 1] == "green") {
            gameSetVector[1] = stoi(game[i]);
        } else if (game[i + 1] == "blue") {
            gameSetVector[2] = stoi(game[i]);
        }
    }

    return gameSetVector;
}
bool allValid(vector<string> gameSet, vector<int> config) {
    // [[3,4,0], []]
    vector<vector<int>> cubes;
    for (auto game : gameSet) {
        game = lstrip(game);
        auto gameSplit = splitString(game, ' ');
        vector<int> cubesVector = gameToVector(gameSplit);
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
        vector<string> gameSet = splitString(parsedLine, ';');
        if (allValid(gameSet, config)) {
            currentSum += id;
        }

    }
    cout << "res is " << currentSum << endl;

    return 0;
}