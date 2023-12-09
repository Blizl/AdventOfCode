#include <iostream>

#include "../utils.h"
#include <algorithm>
using namespace std;

int predictNextValue(vector<int> values) {
    vector<vector<int> > diffList = {values};
    while (true) {
        vector<int> diffs;
        int currentDiffSum = 0;
        for (int i = 1; i < values.size(); i++) {
            int diff = values[i] - values[i - 1];
            currentDiffSum += diff;
            diffs.push_back(diff);
        }
        diffList.push_back(diffs);
        if (currentDiffSum == 0) {
            break;
        }
        values = diffs;
    }
    reverse(diffList.begin(), diffList.end());
    for (int i = 0; i < diffList.size() - 1; i++) {
        vector<int> previousList = diffList[i];
        int firstElementPrevious = previousList[0];
        vector<int> currentList = diffList[i+1];
        int firstElementCurrent = currentList[0];
        diffList[i + 1].insert(diffList[i+1].begin(), firstElementCurrent - firstElementPrevious);
   }

    return diffList[diffList.size() - 1][0];
}

int main() {
    int currentSum = 0;
    vector<string> lines = readLines("input.txt");
    for (auto line : lines) {
        vector<string> lineVector = splitString(line, ' ');
        vector<int> lineVectorTransformed;
        transform(lineVector.begin(), lineVector.end(),
                  back_inserter(lineVectorTransformed),
                  [](string& str) { return stoi(str); });
        int nextValue = predictNextValue(lineVectorTransformed);
        cout << "line vector transformed is " << lineVectorTransformed << endl;
        currentSum += nextValue;
    }

    cout << "Current sum is " << currentSum << endl;
    return 0;
}