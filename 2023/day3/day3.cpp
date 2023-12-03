#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../utils.h"

using namespace std;

bool isSymbol(char symbol) { return !isdigit(symbol) && symbol != '.'; }

bool hasSymbolHorizontally(vector<string> lines, int i, int startIndex,
                           int endIndex) {
    bool left = false;
    if (startIndex > 0) {
        left = isSymbol(lines[i][startIndex - 1]);
    }
    bool right = false;
    if (endIndex < lines[i].length() - 1) {
        right = isSymbol(lines[i][endIndex + 1]);
    }

    return left || right;
}
bool hasSymbolVertically(vector<string> lines, int i, int startIndex,
                         int endIndex) {
    // need to check top or bottom depending on the length of the digit
    bool top = false;
    if (i > 0) {
        for (int j = startIndex; j < endIndex + 1; j++) {
            if (isSymbol(lines[i - 1][j])) {
                top = true;
                break;
            }
        }
    }

    bool bottom = false;
    if (i < lines[i].length() - 1) {
        for (int j = startIndex; j < endIndex + 1; j++) {
            if (isSymbol(lines[i + 1][j])) {
                bottom = true;
                break;
            }
        }
    }

    return top || bottom;
}
bool hasSymbolDiagonally(vector<string> lines, int i, int startIndex,
                         int endIndex) {
    // top left
    bool topLeft = false;
    if (i > 0 && startIndex > 0) {
        topLeft = isSymbol(lines[i - 1][startIndex - 1]);
    }
    // top right
    bool topRight = false;
    if (i > 0 && endIndex < lines[i].length() - 1) {
        topRight = isSymbol(lines[i - 1][endIndex + 1]);
    }
    // bottom left
    bool bottomLeft = false;
    if (i < lines.size() - 1 && startIndex > 0) {
        bottomLeft = isSymbol(lines[i + 1][startIndex - 1]);
    }
    // bottom right
    bool bottomRight = false;
    if (i < lines.size() - 1 && endIndex < lines[i].length() - 1) {
        bottomRight = isSymbol(lines[i + 1][endIndex + 1]);
    }
    return topLeft || topRight || bottomLeft || bottomRight;
}
bool isAdjToGear(vector<string> lines, int i, int startIndex, int endIndex) {
    // is only a part number if horizontally, diagonally, or vertically has
    // a symbol

    return hasSymbolHorizontally(lines, i, startIndex, endIndex) ||
           hasSymbolVertically(lines, i, startIndex, endIndex) ||
           hasSymbolDiagonally(lines, i, startIndex, endIndex);
}
int findEndIndex(string line, int startIndex) {
    string substring = line.substr(startIndex, line.length());
    for (int i = startIndex; i < line.length(); i++) {
        if (!isdigit(line[i])) {
            return i;
        }
    }
    return line.length();
}

int main() {
    vector<string> lines = readLines("input.txt");
    int currentSum = 0;
    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[i].length(); j++) {
            // move on if it's not a digit
            if (!isdigit(lines[i][j])) {
                continue;
            }
            int endIndex = findEndIndex(lines[i], j);
            int num = stoi(lines[i].substr(j, endIndex - j));
            // cout << "num is " << num << endl;
            if (isAdjToGear(lines, i, j, endIndex - 1)) {
                cout << "adding " << num << " to current sum" << endl;
                currentSum += num;
            }

            j = endIndex;
        }
    }

    cout << "Sum is " << currentSum << endl;

    return 0;
}
