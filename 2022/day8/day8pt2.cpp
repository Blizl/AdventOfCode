#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int findScenicScoreLeft(vector<vector<int> > &grid, int curRow, int curCol,
                        int currentHeight) {
    if (curCol < 0) {
        return 0;
    }
    if (grid[curRow][curCol] < currentHeight) {
        return 1 +
               findScenicScoreLeft(grid, curRow, curCol - 1, currentHeight);
    } else if (grid[curRow][curCol] == currentHeight) {
        return 1;
    }
    return 1;
}

int findScenicScoreRight(vector<vector<int> > &grid, int curRow, int curCol,
                        int currentHeight) {
    if (curCol >= grid[0].size()) {
        return 0;
    }
    if (grid[curRow][curCol] < currentHeight) {
        return 1 +
               findScenicScoreRight(grid, curRow, curCol + 1, currentHeight);
    } else if (grid[curRow][curCol] == currentHeight) {
        return 1;
    }
    return 1;
}
int findScenicScoreTop(vector<vector<int> > &grid, int curRow, int curCol,
                         int currentHeight) {
    if (curRow < 0 ) {
        return 0;
    }

    if (grid[curRow][curCol] < currentHeight) {
        return 1 +
               findScenicScoreTop(grid, curRow -1, curCol, currentHeight);
    } else if (grid[curRow][curCol] == currentHeight) {
        return 1;
    }
    return 1;
}
int findScenicScoreBottom(vector<vector<int> > &grid, int curRow, int curCol,
                       int currentHeight) {
    if (curRow >= grid.size()) {
        return 0;
    }
    if (grid[curRow][curCol] < currentHeight) {
        return 1 + findScenicScoreBottom(grid, curRow +1, curCol , currentHeight);
    } else if (grid[curRow][curCol] == currentHeight) {
        return 1;
    }
    return 1;
}

int findScenicScore(vector<vector<int> > &grid, int rows, int columns, int curRow,
               int curCol, int currentHeight) {
    if (curRow == 0 || curCol == 0 || curRow == rows -1|| curCol == columns -1) {
        return 0;
    }

    cout << "row: " << curRow << " col: " << curCol << " currentHeight: " << grid[curRow][curCol] << endl;
    // check left trees to see if all of them < currentHeight
    int leftScore = findScenicScoreLeft(grid, curRow , curCol -1, currentHeight);
    // cout << "left score is " << leftScore << endl;

    // check right trees to see if all of them < currentHeight
    int rightScore =
        findScenicScoreRight(grid, curRow, curCol + 1, currentHeight);
    // cout << "right score is " << rightScore << endl;

    // check top trees to see if all of them < currentHeight
    int topScore =
        findScenicScoreTop(grid, curRow -1, curCol , currentHeight);
    // cout << "top score is " << topScore << endl;

    // check bottom trees to see if all of them < currentHeight
    int bottomScore =
        findScenicScoreBottom(grid, curRow +1, curCol, currentHeight);
    // cout << "bottom score is " << bottomScore << endl;

    int totalScenicScore = leftScore * rightScore * topScore * bottomScore;
    cout << "total score is " << totalScenicScore << endl;
    return totalScenicScore;
}

void dfs(vector<vector<int> > &grid, int rows, int columns, int curRow,
         int curCol, int &maxScenicScore) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            int currentHeight = grid[i][j];
            int scenicScore =
                findScenicScore(grid, rows, columns, i, j, currentHeight);
            maxScenicScore = max(scenicScore, maxScenicScore);
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
    int maxScenicScore = 0;
    dfs(grid, m, n, 0, 0, maxScenicScore);
    cout << "Max scenic score is " << maxScenicScore << endl;
}
