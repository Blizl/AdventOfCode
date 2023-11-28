#include <iostream>
#include <fstream>
#include <unordered_set>

bool contains_four_unique(int start, int end, std::string line) {
    std::unordered_set<char> set;
    for (int i = start; i <= end; i++) {
        if (set.find(line[i]) != set.end()) {
            return false;
        }
        set.insert(line[i]);
    }
    return set.size() == 4;
}

int find_first_distinct_five_characters_index(std::string line) {
    int start = 0;
    while (start < line.length() && start + 3 < line.length()) {
        if (contains_four_unique(start, start + 3, line)) {
            return start + 4;
        }
        start++;
    }
    return 0;

}

int main() { 
    auto start = std::chrono::high_resolution_clock::now();

    std::ifstream inputFile("input.txt");
    std::string line;
    int res;
    std::getline(inputFile, line);
    res = find_first_distinct_five_characters_index(line);

    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the elapsed time in milliseconds
    auto duration = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(end - start);

    std::cout << "Count before 5 distinct: " << res << std::endl;
    std::cout << "Time used (milliseconds): " << duration.count() << std::endl;

    return 0;

}

