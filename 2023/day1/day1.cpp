#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int findDigits(string line) {
    string digitStr;
    for (int i = 0; i < line.length(); i++) {
        if (isdigit(line[i])) {
            if (digitStr.size() == 2) {
                digitStr.pop_back();
            }
            digitStr += line[i];
        }
    }
    if (digitStr.size() == 1) {
        digitStr += digitStr[0];
    }
    return stoi(digitStr);
}

int main() {
    std::ifstream inputFile("input.txt");
    std::string line;
    int currentSum = 0;

    while (std::getline(inputFile, line)) {
        // Process each line as needed
        currentSum += findDigits(line);
    }
    cout << "currentSum is " << currentSum << endl;




    return 0;
}