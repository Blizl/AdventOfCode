#include <iostream>
#include <fstream>
#include <queue>

int main() {
    std::ifstream inputFile("input.txt");
    std::string line;
    int currentSum = 0;
    std::priority_queue<int> pq;

    while (std::getline(inputFile, line)) {
        // Process each line as needed
        if (line == "") {
            pq.push(currentSum);
            currentSum = 0;
            continue;
        }

        currentSum += std::stoi(line);
    }
    int first = pq.top();
    std::cout << "first is " << first << std::endl;
    pq.pop();
    int second = pq.top();
    std::cout << "second is " << second << std::endl;
    pq.pop();
    int third = pq.top();
    std::cout << "third is " << third << std::endl;
    pq.pop();
    std::cout << "top 3 sum is " << (first + second + third) << "\n";

    return 0;
}
