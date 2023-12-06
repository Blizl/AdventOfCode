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
    long long times = 53916768;
    long long distance = 250133010811025;
    unordered_map<long long, long long> timesMap;
    for (long long j = 0; j <= times; j++) {
        // hold for 1s = 1m/s
        timesMap[j] = (times - j) * j;
    }

    long long recordBeat = 0;
    for (auto pair : timesMap) {
        if (pair.second > distance) {
            recordBeat++;
        }
    }

    cout << "res is " << recordBeat << endl;
}