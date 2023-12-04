#include <iostream>
#include "../utils.h"
#include <vector>
#include <string>
#include <cmath>
#include <set>
#include <ranges>
#include <cctype>
#include <queue>

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
    int totalCards = 0;
    unordered_map<int, int> cardCount;
    queue<int> copiesWon;
    for (int i = 0; i < lines.size(); i++) {
        cardCount[i + 1] = 1;
    }

    for (int i = 0; i < lines.size(); i++) {
            string line = lines[i];

            vector<string> card = splitString(
                line.substr(line.find(":") + 1, line.length()), '|');
            set<int> winningNumbers = toSet(card[0]);
            set<int> scratchedNumbers = toSet(card[1]);

            set<int> intersect;
            set_intersection(winningNumbers.begin(), winningNumbers.end(),
                             scratchedNumbers.begin(), scratchedNumbers.end(),
                             std::inserter(intersect, intersect.begin()));
            // cout << "Card: " << i + 1 << endl;
            // cout << "matches are " << intersect.size() << endl;
            for (int k = 0; k < cardCount[i + 1]; k++) {
                for (int j = i + 2; j <= i + intersect.size() + 1; j++) {
                    cardCount[j] = cardCount[j] + 1;
                    // cout << "cardCount[j] is j: " << j
                        //  << "value:  " << cardCount[j] << endl;
                }
            }

        }
        // cout << "card count is " << cardCount << endl;
        for (auto pair: cardCount) {
            totalCards += pair.second;
        }
        cout << "total cards is " << totalCards << endl;
        return 0;
    }
