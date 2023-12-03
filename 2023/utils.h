#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

// Function declarations
void removeAll(std::string& str, char character);

std::vector<std::string> splitString(const std::string& input, char delimiter = ' ');

void lstrip(std::string& s, const std::string& charsToRemove = " \t\r\n");
void rstrip(std::string& s, const std::string& charsToRemove = " \t\r\n");

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "[";
    if (!vec.empty()) {
        std::copy(vec.begin(), vec.end() - 1,
                  std::ostream_iterator<T>(os, ", "));
        os << vec.back();
    }
    os << "]";
    return os;
}

template <typename KeyType, typename ValueType>
std::ostream& operator<<(std::ostream& os,
                         const std::unordered_map<KeyType, ValueType>& map) {
    os << "Map Contents:" << std::endl;
    for (const auto& pair : map) {
        os << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
    }
    return os;
}

vector<std::string> readLines(string file);
#endif  // UTILS_H
