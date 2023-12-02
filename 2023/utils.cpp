
#include "utils.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void removeAll(std::string& str, char character) {
    str.erase(std::remove(str.begin(), str.end(), character), str.end());
}

void lstrip(std::string& str, const std::string& charsToRemove) {
    size_t pos = str.find_first_not_of(charsToRemove);
    if (pos != std::string::npos) {
        str.erase(0, pos);
    } else {
        str.clear();  // If the string contains only whitespace, clear the
                      // entire string
    }
}

void rstrip(std::string& str, const std::string& charsToRemove) {
    size_t pos = str.find_last_not_of(charsToRemove);
    if (pos != std::string::npos) {
        str.erase(pos + 1);
    } else {
        str.clear();  // If the string contains only whitespace, clear the
                      // entire string
    }
}

std::vector<std::string> splitString(const std::string& input, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;

    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}
