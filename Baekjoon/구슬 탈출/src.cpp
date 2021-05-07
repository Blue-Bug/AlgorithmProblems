#include <vector>
#include <queue>
#include <iostream>
using namespace std;

struct twoball {
    int red_row, red_col,blue_row, blue_col,cnt;
    twoball(int a, int b, int c, int d, int e) {
        red_row = a, red_col = b, blue_row = c, blue_col = d, cnt = e;
    }
};

char board[10][10];
int dir[4][2] = { {0,1},{0,-1},{1,0},{-1,0} };
int n, m;

//flag를 사용
int bfs(twoball tb) {
    bool check[10][10][10][10]{ false };
    queue<twoball> q;
    q.push(tb);

    while (!q.empty()) {
        twoball tmp = q.front();
        q.pop();
        if (check[tmp.red_row][tmp.red_col][tmp.blue_row][tmp.blue_col]) {
            continue;
        }
        check[tmp.red_row][tmp.red_col][tmp.blue_row][tmp.blue_col] = true;
        
        for (int i = 0; i < 4; i++) {
            int next_red_row = tmp.red_row;
            int next_red_col = tmp.red_col;
            int next_blue_row = tmp.blue_row;
            int next_blue_col = tmp.blue_col;
            bool escapeFlag = false;
            while (1) {
                next_blue_row += dir[i][0];
                next_blue_col += dir[i][1];
                char next_cell = board[next_blue_row][next_blue_col];
                if (next_cell != '#') {
                    if (next_cell == 'O') {
                        escapeFlag = true;
                        break;
                    }
                }
                else {
                    next_blue_row -= dir[i][0];
                    next_blue_col -= dir[i][1];
                    break;
                }
            }
            if (escapeFlag) continue;
            while (1) {
                next_red_row += dir[i][0];
                next_red_col += dir[i][1];
                char next_cell = board[next_red_row][next_red_col];
                if (next_cell != '#') {
                    if (next_cell == 'O') {
                        if (tmp.cnt + 1 <= 10) {
                            return 1;
                        }
                        escapeFlag = true;
                        break;
                    }
                }
                else {
                    next_red_row -= dir[i][0];
                    next_red_col -= dir[i][1];
                    break;
                }
            }
            if (escapeFlag) continue;
            if (next_red_row == next_blue_row && next_red_col == next_blue_col) {
                //좌표가 같을 경우 하나를 옮긴다
                if (i == 0) {
                    tmp.red_col > tmp.blue_col ? next_blue_col-- : next_red_col--;
                }else if (i == 1) {
                    tmp.red_col > tmp.blue_col ? next_red_col++ : next_blue_col++;
                }else if (i == 2) {
                    tmp.red_row > tmp.blue_row ? next_blue_row-- : next_red_row--;
                }else if (i == 3) {
                    tmp.red_row > tmp.blue_row ? next_red_row++ : next_blue_row++;
                }
            }
            if (!check[next_red_row][next_red_col][next_blue_row][next_blue_col]) {
                q.push(twoball( next_red_row,next_red_col,next_blue_row,next_blue_col,tmp.cnt + 1));
            }
        }
    }
    return 0;
}

int main() {
    cin >> n >> m;
    twoball tb(0,0,0,0,0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> board[i][j];
            if (board[i][j] == 'R') {
                tb.red_row = i;
                tb.red_col = j;
                board[i][j] = '.';
            }
            else if (board[i][j] == 'B') {
                tb.blue_row = i;
                tb.blue_col = j;
                board[i][j] = '.';
            }
        }
    }
    tb.cnt = 0;
    cout <<  bfs(tb);
}