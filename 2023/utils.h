#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;

// Function declarations
void removeAll(std::string& str, char character);

std::vector<std::string> splitString(const std::string& input, char delimiter = ' ');

void lstrip(std::string& s, const std::string& charsToRemove = " \t\r\n");
void rstrip(std::string& s, const std::string& charsToRemove = " \t\r\n");

template <typename T>
void printVector(const std::vector<T>& vec,
                 const std::string& delimiter = " ") {
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i];
        if (i != vec.size() - 1) {
            cout << delimiter;
        }
    }
    cout << endl;
}
#endif  // UTILS_H
