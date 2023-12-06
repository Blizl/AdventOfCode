#include <algorithm>
#include <cctype>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "../utils.h"

using namespace std;

bool isSpaceStringOrNonDigit(const std::string& str) {
    return std::all_of(str.begin(), str.end(),
                       [](char c) {
                           return std::isspace(static_cast<unsigned char>(c));
                       }) ||
           !isStrDigit(str);
}

int main() {
    int res = 1;
    vector<string> lines = readLines("input.txt");
    vector<string> times = splitString(lines[0], ' ');
    vector<string> distances = splitString(lines[1], ' ');
    times.erase(
        std::remove_if(times.begin(), times.end(), isSpaceStringOrNonDigit),
        times.end());
    distances.erase(std::remove_if(distances.begin(), distances.end(),
                                   isSpaceStringOrNonDigit),
                    distances.end());
    vector<int> timesInt = {53, 91, 67, 68};
    vector<int> distancesInt = {250, 1330, 1081, 1025} ;
    vector<unordered_map<int, int> > resList;
    for (int i = 0; i < timesInt.size(); i++) {
        unordered_map<int, int> timesMap;
        for (int j = 0; j <= timesInt[i]; j++) {
            // hold for 1s = 1m/s
            timesMap[j] = (timesInt[i] - j) * j;
        }
        resList.push_back(timesMap);
    }
    for (int i = 0; i < distancesInt.size(); i++) {
        int recordBeat = 0;
        for (auto pair : resList[i]) {
            if (pair.second > distancesInt[i]) {
                recordBeat++;
            }
        }
        res *= recordBeat;
    }

    cout << "res is " << res << endl;
}