#include <vector>
#include <queue>

using namespace std;

//오답이 먼저 도달하는 경우, 이미 방문했던 노드를 다시 방문하는 경우
//짝수는 횡 이동, 홀수는 종 이동
int dir[4][2] = { {0,1},{1,0},{0,-1},{-1,0} };
struct node {
    int row, col, prev_dir, cost;
};

int bfs(int n, vector<vector<int>>& board) {
    queue<node> q;
    q.push({ 0,0,-1,0 });
    vector<vector<int>> check(n, vector<int>(n, 987654321));
    while (!q.empty()) {
        node cur = q.front();
        q.pop();

        if (check[cur.row][cur.col] < cur.cost) continue;
        check[cur.row][cur.col] = cur.cost;

        for (int i = 0; i < 4; i++) {
            int nextRow = cur.row + dir[i][0];
            int nextCol = cur.col + dir[i][1];

            if (nextRow < 0 || nextRow >= n) continue;
            if (nextCol < 0 || nextCol >= n) continue;
            if (board[nextRow][nextCol] == 0) {
                if (cur.prev_dir % 2 == 0) {
                    //이전 방향이 횡이동이었다면
                    if (i % 2 == 0) {
                        q.push({ nextRow,nextCol,i,cur.cost + 100 });
                    }
                    else {
                        q.push({ nextRow,nextCol,i,cur.cost + 600 });
                    }
                }
                else if (cur.prev_dir % 2 == 1) {
                    //이전 방향이 종이동이었다면
                    if (i % 2 == 0) {
                        q.push({ nextRow,nextCol,i,cur.cost + 600 });
                    }
                    else {
                        q.push({ nextRow,nextCol,i,cur.cost + 100 });
                    }
                }
                else if (cur.prev_dir == -1) {
                    //맨처음은 그냥 계산
                    q.push({ nextRow,nextCol,i,cur.cost + 100 });
                }
            }
        }
    }
    return check[n - 1][n - 1];
}

int solution(vector<vector<int>> board) {
    int answer = 0;
    answer = bfs(board.size(), board);
    return answer;
}
