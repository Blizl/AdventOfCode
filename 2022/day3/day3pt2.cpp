#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

std::unordered_map<char, int> priorities = {
    {'a', 1}, {'b', 2}, {'c', 3}, {'d', 4}, {'e', 5}, {'f', 6}, {'g', 7}, {'h', 8},
    {'i', 9}, {'j', 10}, {'k', 11}, {'l', 12}, {'m', 13}, {'n', 14}, {'o', 15},
    {'p', 16}, {'q', 17}, {'r', 18}, {'s', 19}, {'t', 20}, {'u', 21}, {'v', 22},
    {'w', 23}, {'x', 24}, {'y', 25}, {'z', 26},
    {'A', 27}, {'B', 28}, {'C', 29}, {'D', 30}, {'E', 31}, {'F', 32}, {'G', 33},
    {'H', 34}, {'I', 35}, {'J', 36}, {'K', 37}, {'L', 38}, {'M', 39}, {'N', 40},
    {'O', 41}, {'P', 42}, {'Q', 43}, {'R', 44}, {'S', 45}, {'T', 46}, {'U', 47},
    {'V', 48}, {'W', 49}, {'X', 50}, {'Y', 51}, {'Z', 52}
};

template <typename T>
std::unordered_set<T> find_intersection(const std::unordered_set<T>& set) {
    return set;
}

// Recursive function to find intersection of multiple sets
template <typename T, typename... Args>
std::unordered_set<T> find_intersection(const std::unordered_set<T>& set, const Args&... args) {
    std::unordered_set<T> result;

    for (const T& elem : set) {
        bool presentInAll = true;
        // Check if the element exists in all sets
        ((presentInAll = presentInAll && (args.find(elem) != args.end())), ...);
        if (presentInAll) {
            result.insert(elem); // Add the element to the intersection
        }
    }

    return result;
}



int findCommon(std::string line, std::string line2, std::string line3) {
    std::unordered_set<char> set_1(line.begin(), line.end());
    std::unordered_set<char> set_2(line2.begin(), line2.end());
    std::unordered_set<char> set_3(line3.begin(), line3.end());

    std::unordered_set<char> intersection = find_intersection(set_1, set_2, set_3);

    if (!intersection.empty()) {
        return priorities[*(intersection.begin())];
    }
    return 0;
};

int main() {

    std::ifstream inputFile("input.txt");
    std::string line;
   
    int res = 0;
    while (std::getline(inputFile, line)) {
        
         // std::cout << "line is even: " << (line.length() % 2 == 0) << std::endl;
        // for each line we need to split it in half and find the one with duplicates
        std::string second_line; 
        std::getline(inputFile, second_line);
        std::string third_line; 
        std::getline(inputFile, third_line);
        
        res += findCommon(line, second_line, third_line);
    }

    std::cout << "Total priority is " << res << std::endl;
    return 0;
};


