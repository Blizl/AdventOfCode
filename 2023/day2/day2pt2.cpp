#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "../utils.h"
using namespace std;

std::string lstrip(const std::string& s) {
    size_t start = s.find_first_not_of(" ");
    if (start != std::string::npos) {
        return s.substr(start);
    }
    return "";  // Return empty string if there are only spaces
}



vector<int> gameSetToVector(vector<string> gameSet) {
    vector<int> gameSetVector = {0, 0, 0};
    for (int i = 0; i < gameSet.size() - 1; i++) {
        removeAllOccurrences(gameSet[i + 1], ',');
        if (gameSet[i + 1] == "red") {
            gameSetVector[0] = stoi(gameSet[i]);
        } else if (gameSet[i + 1] == "green") {
            gameSetVector[1] = stoi(gameSet[i]);
        } else if (gameSet[i + 1] == "blue") {
            gameSetVector[2] = stoi(gameSet[i]);
        }
    }

    return gameSetVector;
}
int findMinCubesNeeded(vector<string> tokens) {
    // [[3,4,0], []]
    vector<vector<int>> cubes;
    for (auto token : tokens) {
        token = lstrip(token);
        auto gameSet = splitString(token, ' ');
        vector<int> cubesVector = gameSetToVector(gameSet);

        cout << "cubesVector:  ";
        printVector(cubesVector);
        cubes.push_back(cubesVector);
    }
    vector<int> minCubes;
    for (int j = 0; j < 3; j++) {
        int currentMin = INT_MIN;
        for (int i = 0; i < cubes.size(); i++) {
            // 3 since there are only 3 colors
            if (cubes[i][j] > currentMin) {
                currentMin = cubes[i][j];
            }
        }
        minCubes.push_back(currentMin);
    }
    cout << "minCubes: ";
    printVector(minCubes);
    // cube everything
    return minCubes[0] * minCubes[1] * minCubes[2];
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
        int id = stoi(line.substr(5, line.find(":") + 1));
        string parsedLine =
            line.substr(line.find(":") + 2, line.length() - line.find(":"));
        vector<string> tokens = splitString(parsedLine, ';');
        int cubed = findMinCubesNeeded(tokens);
        cout << "cubed is " << cubed << endl;
        currentSum += cubed;
    }
    cout << "res is " << currentSum << endl;

    return 0;
}