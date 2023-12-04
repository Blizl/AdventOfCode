#include <iostream>
#include "../utils.h"
#include <vector>
#include <string>
#include <cmath>
#include <set>
#include <ranges>
#include <cctype>

using namespace std;


bool isStrDigit(string& str) {
    return !str.empty() &&
           std::all_of(str.begin(), str.end(),
                       [](unsigned char c) { return std::isdigit(c); });
}

set<int> toSet(string numbers) {
    set<int> numbersSet;
    vector<string> splitNumbers = splitString(numbers, ' ');
    for (string item : splitNumbers) {
        if (isStrDigit(item)) {
            numbersSet.insert(stoi(item));
        }
    }
    return numbersSet;
}

int main() { 
    vector<string> lines = readLines("input.txt");
    // cout << "lines is " << lines << endl;
    int totalPoints = 0;
    for (auto line : lines) {
        vector<string> card =
            splitString(line.substr(line.find(":") +1, line.length()), '|');
        set<int> winningNumbers = toSet(card[0]);
        set<int> scratchedNumbers = toSet(card[1]);

        set<int> intersect;
        set_intersection(winningNumbers.begin(), winningNumbers.end(),
                         scratchedNumbers.begin(), scratchedNumbers.end(),
                         std::inserter(intersect, intersect.begin()));
        // cout << "winning numbers is " << winningNumbers << endl;
        // cout << "scrated numbers is " << scratchedNumbers << endl;
        // cout << "matched numbers is " << intersect << endl;
        if (!intersect.empty()) {
            totalPoints += (pow(2, intersect.size() - 1));
        }
    }
    cout << "total points is " << totalPoints << endl;
    return 0;
}
