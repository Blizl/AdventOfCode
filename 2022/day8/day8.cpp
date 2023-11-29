#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 0 = left
// 1 = right
// 2 = top
// 3 = bottom
bool isShorterLeft(vector<vector<int> > &grid, int curRow,
               int curCol, int currentHeight) {
    if (curCol < 0) {
        return true;
    }
    return (grid[curRow][curCol] < currentHeight) && isShorterLeft(grid, curRow, curCol -1, currentHeight);
}

bool isShorterRight(vector<vector<int> > &grid, int curRow, int curCol,
                   int currentHeight) {
    if (curCol >= grid[0].size()) {
        return true;
    }

    return (grid[curRow][curCol] < currentHeight) &&
           isShorterRight(grid, curRow, curCol +1, currentHeight);
}
bool isShorterTop(vector<vector<int> > &grid, int curRow, int curCol,
                    int currentHeight) {
    if (curRow < 0 ) {
        return true;
    }
    return (grid[curRow][curCol] < currentHeight) &&
           isShorterTop(grid, curRow -1, curCol, currentHeight);
}
bool isShorterBottom(vector<vector<int> > &grid, int curRow, int curCol,
                  int currentHeight) {
    if (curRow >= grid.size()) {
        return true;
    }
    return (grid[curRow][curCol] < currentHeight) &&
           isShorterBottom(grid, curRow + 1, curCol, currentHeight);
}

bool isVisible(vector<vector<int> > &grid, int rows, int columns, int curRow,
               int curCol, int currentHeight) {
    if (curRow == 0 || curCol == 0 || curRow == rows -1|| curCol == columns -1) {
        // cout << "is visible" << endl;
        return true;
    }

    cout << "row: " << curRow << " col: " << curCol << " currentHeight: " << grid[curRow][curCol] << endl;
    // check left trees to see if all of them < currentHeight
    bool allLeftShorter = isShorterLeft(grid, curRow , curCol -1, currentHeight);

    // check right trees to see if all of them < currentHeight
    bool allRightShorter =
        isShorterRight(grid, curRow, curCol + 1, currentHeight);

    // check top trees to see if all of them < currentHeight
    bool allTopShorter = isShorterTop(grid, curRow - 1, curCol, currentHeight);

    // check bottom trees to see if all of them < currentHeight
    bool allBottomShorter =
        isShorterBottom(grid, curRow + 1, curCol, currentHeight);


    bool isVisible =  allLeftShorter || allRightShorter || allTopShorter ||
           allBottomShorter;
    if (isVisible) {
        cout << "is visible: " <<  endl;
    }
    return isVisible;
}

void dfs(vector<vector<int> > &grid, int rows, int columns, int curRow,
         int curCol, int &visibleTress) {
    if (curRow < 0 || curCol < 0 || curRow >= rows || curCol >= columns) {
        return;
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            int currentHeight = grid[i][j];
            if (isVisible(grid, rows, columns, i, j, currentHeight)) {
                visibleTress++;
            }
        }
    }
  
    // go left
    // go right
    // go up
    // go bottom
}

int main() {
    vector<string> lines;
    string line;
    ifstream inputFile("input.txt");
    while (getline(inputFile, line)) {
        lines.push_back(line);
    }
    int m = lines.size();
    int n = lines[0].length();
    vector<vector<int> > grid;
    for (int i = 0; i < m; i++) {
        vector<int> currentRow;
        for (int j = 0; j < n; j++) {
            int value = lines[i][j] - '0';
            currentRow.push_back(value);
        }
        grid.push_back(currentRow);
    }
    int visibleTrees = 0;
    dfs(grid, m, n, 0, 0, visibleTrees);
    cout << "visible trees are " << visibleTrees << endl;
}
