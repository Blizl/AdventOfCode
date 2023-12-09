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
        cout << "diffs is " << diffs << endl;
        diffList.push_back(diffs);
        if (currentDiffSum == 0) {
            break;
        }
        values = diffs;
    }
    reverse(diffList.begin(), diffList.end());
    for (int i = 0; i < diffList.size() - 1; i++) {
        vector<int> previousList = diffList[i];
        int lastElementPrevious = previousList[previousList.size() - 1];
        vector<int> currentList = diffList[i+1];
        int lastElementCurrent = currentList[currentList.size() - 1];
        // cout << "lastelement previous is " << lastElementPrevious << endl;
        // cout << "lastelement current is " << lastElementCurrent << endl;
        diffList[i + 1].push_back(lastElementCurrent + lastElementPrevious);
    }

    return diffList[diffList.size() - 1][diffList[diffList.size() - 1].size() -1];
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