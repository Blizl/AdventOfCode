#include <iostream>
#include <fstream>
#include <unordered_map>
#include <set>
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

std::set<char> find_intersection(std::set<char> first_set, 
                                           std::set<char> second_set) {
    std::set<char> intersection;
    std::set_intersection(
        first_set.begin(), first_set.end(),
        second_set.begin(), second_set.end(),
        std::inserter(intersection, intersection.begin())
    );
    return intersection;

}


int findDuplicate(std::string line) {
    std::string first_rucksack = line.substr(0, line.length() /2);
    std::string second_rucksack = line.substr(line.length() /2, line.length() - line.length() / 2);
    std::set<char> first_rucksack_set(first_rucksack.begin(), first_rucksack.end());
    std::set<char> second_rucksack_set(second_rucksack.begin(), second_rucksack.end());

    std::set<char> intersection = find_intersection(first_rucksack_set, second_rucksack_set);

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
        res += findDuplicate(line);
    }

    std::cout << "Total priority is " << res << std::endl;
    return 0;
};


