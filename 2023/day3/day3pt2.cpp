#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../utils.h"

using namespace std;

struct Gear {
    int x;
    int y;

    Gear(int x, int y) : x(x), y(y) {}

    bool operator==(const Gear& other) const {
        return (x == other.x) && (y == other.y);
    }

    friend std::ostream& operator<<(std::ostream& os, const Gear& gear) {
        os << "Gear(" << gear.x << ", " << gear.y << ")";
        return os;
    }
};

namespace std {
template <>
struct hash<Gear> {
    size_t operator()(const Gear& g) const {
        return hash<int>()(g.x) ^ (hash<int>()(g.y) << 1);
    }
};
}  // namespace std

int findEndIndex(string line, int startIndex) {
    for (int i = startIndex; i < line.length(); i++) {
        if (!isdigit(line[i])) {
            return i;
        }
    }
    return line.length();
}

bool isSymbol(char symbol) { return symbol == '*'; }

vector<Gear> findGearsHorizontally(vector<string> lines, int i, int startIndex,
                                   int endIndex) {
    bool left = false;
    vector<Gear> gears;
    if (startIndex > 0) {
        left = isSymbol(lines[i][startIndex - 1]);
        if (left) {
            gears.push_back(Gear(i, startIndex - 1));
        }
    }
    bool right = false;
    if (endIndex < lines[i].length() - 1) {
        right = isSymbol(lines[i][endIndex + 1]);
        if (right) {
            gears.push_back(Gear(i, endIndex + 1));
        }
    }

    return gears;
}
vector<Gear> findGearsVertically(vector<string> lines, int i, int startIndex,
                                 int endIndex) {
    // need to check top or bottom depending on the length of the digit
    vector<Gear> gears;
    bool top = false;
    if (i > 0) {
        for (int j = startIndex; j < endIndex + 1; j++) {
            if (isSymbol(lines[i - 1][j])) {
                top = true;
                gears.push_back(Gear(i - 1, j));
                break;
            }
        }
    }

    bool bottom = false;
    if (i < lines[i].length() - 1) {
        for (int j = startIndex; j < endIndex + 1; j++) {
            if (isSymbol(lines[i + 1][j])) {
                bottom = true;
                gears.push_back(Gear(i + 1, j));
                break;
            }
        }
    }

    return gears;
}
vector<Gear> findGearsDiagonally(vector<string> lines, int i, int startIndex,
                                 int endIndex) {
    vector<Gear> gears;
    // top left
    bool topLeft = false;
    if (i > 0 && startIndex > 0) {
        topLeft = isSymbol(lines[i - 1][startIndex - 1]);
        if (topLeft) {
            gears.push_back(Gear(i - 1, startIndex - 1));
        }
    }
    // top right
    bool topRight = false;
    if (i > 0 && endIndex < lines[i].length() - 1) {
        topRight = isSymbol(lines[i - 1][endIndex + 1]);
        if (topRight) {
            gears.push_back(Gear(i - 1, endIndex + 1));
        }
    }
    // bottom left
    bool bottomLeft = false;
    if (i < lines.size() - 1 && startIndex > 0) {
        bottomLeft = isSymbol(lines[i + 1][startIndex - 1]);
        if (bottomLeft) {
            gears.push_back(Gear(i + 1, startIndex - 1));
        }
    }
    // bottom right
    bool bottomRight = false;
    if (i < lines.size() - 1 && endIndex < lines[i].length() - 1) {
        bottomRight = isSymbol(lines[i + 1][endIndex + 1]);
        if (bottomRight) {
            gears.push_back(Gear(i + 1, endIndex + 1));
        }
    }
    return gears;
}
pair<bool, unordered_set<Gear> > isAdjToGear(vector<string> lines, int i,
                                             int startIndex, int endIndex) {
    // is only a part number if horizontally, diagonally, or vertically has
    // a symbol
    vector<Gear> gearsHorizontally =
        findGearsHorizontally(lines, i, startIndex, endIndex);

    vector<Gear> gearsVertically =
        findGearsVertically(lines, i, startIndex, endIndex);
    vector<Gear> gearsDiagonally =
        findGearsDiagonally(lines, i, startIndex, endIndex);
    unordered_set<Gear> gears;

    for (auto& gear : gearsHorizontally) {
        gears.insert(gear);
    }

    for (auto& gear : gearsVertically) {
        gears.insert(gear);
    }
    for (auto& gear : gearsDiagonally) {
        gears.insert(gear);
    }

    return make_pair((!gearsHorizontally.empty() || !gearsVertically.empty() ||
                      !gearsDiagonally.empty()),
                     gears);
}

int main() {
    vector<string> lines = readLines("input.txt");
    int currentSum = 0;
    unordered_map<Gear, vector<int> > gearMap;
    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[i].length(); j++) {
            // move on if it's not a digit
            if (!isdigit(lines[i][j])) {
                continue;
            }
            int endIndex = findEndIndex(lines[i], j);
            int num = stoi(lines[i].substr(j, endIndex - j));
            pair<bool, unordered_set<Gear> > pair =
                isAdjToGear(lines, i, j, endIndex - 1);
            if (pair.first) {
                for (auto& gear : pair.second) {
                    auto it = gearMap.find(gear);
                    if (it != gearMap.end()) {
                        gearMap[gear].push_back(num);
                    } else {
                        vector<int> newVector;
                        newVector.push_back(num);
                        gearMap[gear] = newVector;
                    }
                }
            }

            j = endIndex;
        }
    }
    cout << gearMap << endl;
    for (auto& pair: gearMap) {
        if (pair.second.size() == 2) {
            currentSum += (pair.second[0] * pair.second[1]);
        }
    }


    cout << "Sum is " << currentSum << endl;

    return 0;
}
