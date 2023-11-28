
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

bool fully_overlaps(std::pair<int, int> range1, std::pair<int, int> range2) {
    return (range1.first <= range2.first && range1.second >= range2.second) || 
    (range2.first <= range1.first && range2.second >= range1.second);
}

int main() { 
    std::ifstream inputFile("input.txt");
    std::string line;
    int res = 0;
    while (std::getline(inputFile, line)) {
	// split by comma 
	std::pair<int, int> range1 = split(line, 0);
	std::pair<int, int> range2 = split(line, 1);
	// 
	if (fully_overlaps(range1, range2)) {
	    res++;
	}
    }

    std::cout << "Test cases for split, should all == 1" << std::endl;
    std::cout << "Split test case 1: 3-5, 7-8, first range " << (split("3-5,7-8", 0) == std::make_pair(3,5)) << std::endl;
    std::cout << "Split test case 2: 3-5, 7-8 second range " << (split("3-5,7-8", 1) == std::make_pair(7,8)) << std::endl;
    std::cout << "Split test case 3: 10-13, 15-30, first range " << (split("10-13,15-30", 0) == std::make_pair(10,13)) << std::endl;
    std::cout << "Split test case 4: 10-13, 15-30, second range " << (split("10-13,15-30", 1) == std::make_pair(15,30)) << std::endl;


    std::cout << "Number of pairs overlapping is " << res << std::endl;

    return 0;



}
