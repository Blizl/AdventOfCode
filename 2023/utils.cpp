
#include "utils.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void removeAllOccurrences(std::string& str, char character) {
    str.erase(std::remove(str.begin(), str.end(), character), str.end());
}

std::string lstrip(const std::string& s) {
    size_t start = s.find_first_not_of(" ");
    if (start != std::string::npos) {
        return s.substr(start);
    }
    return "";  // Return empty string if there are only spaces
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
