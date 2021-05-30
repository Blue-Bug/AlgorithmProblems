#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

vector<vector<int>> graph;
int n, q;
int maxN;
int dir[4][2] = { {0,1},{1,0},{-1,0},{0,-1} };

void rotate_graph(int rowStart, int rowEnd, int colStart, int colEnd) {
    vector<int> tmp;
    for (int i = rowEnd - 1; i >= rowStart; i--) {
        for (int j = colStart; j < colEnd; j++) {
            tmp.push_back(graph[i][j]);
        }
    }
    int idx = 0;
    for (int j = colStart; j < colEnd; j++) {
        for (int i = rowStart; i < rowEnd; i++) {
            graph[i][j] = tmp[idx++];
        }
    }
    
}

void cut_graph(int cutSize) {
    int rowStart = 0;
    int rowEnd = cutSize;
    int colStart = 0;
    int colEnd = cutSize;
    while (1) {
        rotate_graph(rowStart, rowEnd, colStart, colEnd);
        if (rowEnd == maxN && colEnd == maxN) return;
        if (colEnd != maxN) {
            colStart = colEnd;
            colEnd += cutSize;
        }
        else {
            colStart = 0;
            colEnd = cutSize;
            rowStart = rowEnd;
            rowEnd += cutSize;
        }
    }
}

void shrinkIce() {
    vector<vector<int>> graph_copy = graph;
    for (int i = 0; i < maxN; i++) {
        for (int j = 0; j < maxN; j++) {
            int cnt = 0;
            for (int k = 0; k < 4; k++) {
                int nextRow = i + dir[k][0];
                int nextCol = j + dir[k][1];
                if (nextRow < 0 || nextRow >= maxN) continue;
                if (nextCol < 0 || nextCol >= maxN) continue;
                if (graph[nextRow][nextCol] != 0) cnt++;
            }
            if (cnt < 3) {
                graph_copy[i][j]--;
                if (graph_copy[i][j] < 0) {
                    graph_copy[i][j] = 0;
                }
            }
        }
    }
    graph = graph_copy;
}

int getCell(int row, int col) {
    queue<pair<int, int>> q;
    q.push({ row,col });
    int cnt = 0;
    bool check[64][64]{ false };
    while (!q.empty()) {
        int curRow = q.front().first;
        int curCol = q.front().second;
        q.pop();
        if (check[curRow][curCol]) continue;
        check[curRow][curCol] = true;
        cnt++;
        for (int i = 0; i < 4; i++) {
            int nextRow = curRow + dir[i][0];
            int nextCol = curCol + dir[i][1];
            if (nextRow < 0 || nextRow >= maxN) continue;
            if (nextCol < 0 || nextCol >= maxN) continue;
            if (graph[nextRow][nextCol] != 0) {
                q.push({ nextRow,nextCol });
            }
        }
    }
    if (cnt == 1) {
        return 0;
    }
    return cnt;
}

int main() {
    cin >> n >> q;
    maxN = pow(2, n);
    graph = vector<vector<int>>(maxN, vector<int>(maxN));
    for (int i = 0; i < maxN; i++) {
        for (int j = 0; j < maxN; j++) {
            cin >> graph[i][j];
        }
    }
    int cutSize = 0;
    for (int i = 0; i < q; i++) {
        cin >> cutSize;
        //자르기 회전
        cutSize = pow(2, cutSize);
        if (cutSize != 1) {
            cut_graph(cutSize);
        }
        //줄이기
        shrinkIce();
    }
    int sum = 0;
    int maxIce = 0;
    //얼음 합 구하기
    for (int i = 0; i < maxN; i++) {
        for (int j = 0; j < maxN; j++) {
            if (graph[i][j] != 0) {
                int tmpIce = getCell(i, j);
                if (maxIce < tmpIce) {
                    maxIce = tmpIce;
                }
            }
            sum += graph[i][j];
        }
    }
    cout << sum << '\n';
    //덩어리 구하기
    cout << maxIce;
}