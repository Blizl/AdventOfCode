
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>


std::pair<int, int> to_pair(std::string range) {

    std::string token;
    std::stringstream ss(range);
    std::vector<std::string> tokens;
    while (std::getline(ss, token, '-')) {
        tokens.push_back(token);
    }
    return std::make_pair(std::stoi(tokens[0]), std::stoi(tokens[1]));
}

std::pair<int, int> split(std::string line, int index) {
    std::string token;
    std::stringstream ss(line);
    std::vector<std::string> tokens;
    while (std::getline(ss, token, ',')) {
        tokens.push_back(token);
    }
    return to_pair(tokens[index]);
}

bool overlaps(std::pair<int, int> r1, std::pair<int, int> r2) {
    return (r1.first <= r2.second && r2.first <= r1.second);
}

int main() { 
    auto start = std::chrono::high_resolution_clock::now();

    std::ifstream inputFile("input.txt");
    std::string line;
    int res = 0;
    while (std::getline(inputFile, line)) {
	// split by comma 
        std::pair<int, int> range1 = split(line, 0);
        std::pair<int, int> range2 = split(line, 1);
        // 
        if (overlaps(range1, range2)) {
            res++;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the elapsed time in milliseconds
    auto duration = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(end - start);

    std::cout << "Number of pairs overlapping is " << res << std::endl;
    std::cout << "Time used (milliseconds): " << duration.count() << std::endl;

    return 0;

}
