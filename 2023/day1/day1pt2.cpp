#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

unordered_map<std::string, int> wordNumbers = {
    {"one", 1}, {"two", 2},   {"three", 3}, {"four", 4}, {"five", 5},
    {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

bool containsNumber(string line) {
    bool isNum = false;
    for (int i = 0; i < line.length(); i++) {
        for (int j = i + 1; j <= line.length(); j++) {
            // cout << "checking if is number: " << line.substr(i, j -i) << endl;
            isNum =
                wordNumbers.find(line.substr(i, j -i)) != wordNumbers.end();

            if (isNum) {
                return true;
            }
        }
    }
    return isNum;
}

string toNumber(string line) {
    cout << "Line in toNumber is: " << line << endl;
    for (int i = 0; i < line.length(); i++) {
        for (int j = i + 1; j <= line.length(); j++) {
            bool isNum =
                wordNumbers.find(line.substr(i, j -i)) != wordNumbers.end();
            if (isNum) {
                return to_string(wordNumbers[line.substr(i, j-i)]);
            }
        }
    }
    return "";
}

int findDigits(string line) {
    string digitStr;
    int startOfStr = INT_MAX;
    for (int i = 0; i < line.length(); i++) {
        if (isdigit(line[i])) {
            if (digitStr.size() == 2) {
                digitStr.pop_back();
            }
            digitStr += line[i];
            startOfStr = INT_MAX;
        } else {
            if (startOfStr == INT_MAX) {
                startOfStr = i;
            } else {
                if (containsNumber(line.substr(startOfStr, i +1))) {
                    if (digitStr.size() == 2) {
                        digitStr.pop_back();
                    }
                    digitStr += toNumber(line.substr(startOfStr, i +1));
                    startOfStr = INT_MAX;
                } 
            }
        }
    }
    if (digitStr.size() == 1) {
        digitStr += digitStr[0];
    }
    cout << "digits are " << digitStr << endl;
    return stoi(digitStr);
};

int main() {
    std::ifstream inputFile("input.txt");
    std::string line;
    int currentSum = 0;

    while (std::getline(inputFile, line)) {
        // Process each line as needed
        currentSum += findDigits(line);
    }
    cout << "currentSum is " << currentSum << endl;
    cout << "(containsNumber) Test case 1: one2: "
         << boolalpha << containsNumber("one2") << endl;
    cout << "(containsNumber) Test case 2: 2 " << boolalpha
         << !containsNumber("2") << endl;
    cout << "(containsNumber) Test case 3: nine " << boolalpha
         << containsNumber("nine") << endl;

    cout << "(toNumber) Test case 4: one " << boolalpha
         << (toNumber("one") == "1") << endl;
    cout << "(toNumber) Test case 5: one " << boolalpha
         << (toNumber("kasjdfkjdsone") == "1") << endl;
    cout << "(toNumber) Test case 6: two " << boolalpha
         << (toNumber("kasjdfkjdstwoaksdjfs") == "2") << endl;

    return 0;
}