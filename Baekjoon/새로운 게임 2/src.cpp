#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct node {
    int row, col, dir;
};

//오,왼,위,아
int dir[4][2] = { {0,1},{0,-1},{-1,0} ,{1,0} };
int cell[13][13];
//번호,방향
deque<pair<int,int>> board[13][13];
vector<node> chess(11);
int n, k, cnt =1;

bool move() {
    for (int i = 1; i <= k; i++) {
        vector<pair<int, int>> red_vec;
        node it = chess[i];
        int nextRow = it.row + dir[it.dir][0];
        int nextCol = it.col + dir[it.dir][1];
        int color = 0;

        if (nextRow < 1 || nextRow > n) color = 2;
        else if (nextCol < 1 || nextCol > n) color = 2;
        else color = cell[nextRow][nextCol];
        
        //0은 흰색, 1은 빨간색, 2는 파란색
        if (color == 0) {
            //흰색은 위에 있는 것들과 그냥 이동
            for (int j = 0; j < board[it.row][it.col].size(); j++) {
                if (board[it.row][it.col][j].first == i) {
                    int remove = board[it.row][it.col].size() - j;
                    for (int k = j; k < board[it.row][it.col].size(); k++) {
                        board[nextRow][nextCol]
                            .push_back({ board[it.row][it.col][k].first,board[it.row][it.col][k].second });
                        //움직였으니 갱신
                        chess[board[it.row][it.col][k].first]
                            = { nextRow,nextCol,board[it.row][it.col][k].second };
                    }
                    if (board[nextRow][nextCol].size() >= 4) {
                        return false;
                    }
                    while (remove--) {
                        board[it.row][it.col].pop_back();
                    }
                    break;
                }
            }
        }
        else if (color == 1) {
            //빨간색은 이동한 후 뒤집어서 넣는다.
            for (int j = 0; j < board[it.row][it.col].size(); j++) {
                if (board[it.row][it.col][j].first == i) {
                    int remove = board[it.row][it.col].size() - j;
                    for (int k = j; k < board[it.row][it.col].size(); k++) {
                        red_vec
                            .push_back({ board[it.row][it.col][k].first,board[it.row][it.col][k].second });
                        chess[board[it.row][it.col][k].first]
                            = { nextRow,nextCol,board[it.row][it.col][k].second };
                    }
                    while (remove--) {
                        board[it.row][it.col].pop_back();
                    }
                    break;
                }
            }
            if (red_vec.size() + board[nextRow][nextCol].size() >= 4) {
                return false;
            }
            for (int j = red_vec.size() - 1; j >= 0 ; j--) {
                board[nextRow][nextCol].push_back({ red_vec[j].first,red_vec[j].second });
            }
        }
        else if (color == 2) {
            bool flag = false;
            //파란색은 방향을 반대로 바꾸고 한칸 이동, 이동하려는 칸이 파란색이면 멈춤
            //만약 파란색이 바깥으로 가려는 파란색이라면
            for (int j = 0; j < board[it.row][it.col].size(); j++) {
                if (board[it.row][it.col][j].first == i) {
                    int remove = board[it.row][it.col].size() - j;
                    //움직였으니 갱신
                    int nextDir = board[it.row][it.col][j].second;
                    if (nextDir % 2 == 0) {
                        nextDir += 1;
                    }
                    else {
                        nextDir -= 1;
                    }
                    nextRow = it.row + dir[nextDir][0];
                    nextCol = it.col + dir[nextDir][1];
                    chess[board[it.row][it.col][j].first].dir = nextDir;
                    board[it.row][it.col][j].second = nextDir;
                    //범위를 벗어나는지 체크(방향만 바꾸고 움직이지 않는다)
                    if (nextRow < 1 || nextRow > n) break;
                    if (nextCol < 1 || nextCol > n) break;
                    if (cell[nextRow][nextCol] == 2) break;

                    for (int k = j; k < board[it.row][it.col].size(); k++) {
                        //다음 칸도 파란색이라면 멈춤
                        if (cell[nextRow][nextCol] == 1) {
                            flag = true;
                            red_vec.push_back({ board[it.row][it.col][k].first,board[it.row][it.col][k].second });
                        }
                        else if (cell[nextRow][nextCol] == 0) {
                            //그냥 이동
                            flag = true;
                            board[nextRow][nextCol]
                                .push_back({ board[it.row][it.col][k].first,board[it.row][it.col][k].second });
                        }
                        chess[board[it.row][it.col][k].first]
                            = { nextRow,nextCol,board[it.row][it.col][k].second };
                    }
                    
                    if (board[nextRow][nextCol].size() >= 4) {
                        return false;
                    }
                    if (flag) {
                        while (remove--) {
                            board[it.row][it.col].pop_back();
                        }
                        for (int j = red_vec.size() - 1; j >= 0; j--) {
                            board[nextRow][nextCol].push_back({ red_vec[j].first,red_vec[j].second });
                        }
                        if (board[nextRow][nextCol].size() >= 4) {
                            return false;
                        }
                    }
                    break;
                }
            }
        }
    }
    return true;
}

int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> cell[i][j];
        }
    }

    int row, col, direction;
    for (int i = 1; i <= k; i++) {
        cin >> row >> col >> direction;
        board[row][col].push_back({ i,direction - 1 });
        chess[i] = { row,col,direction-1 };
    }

    while (1) {
        if (cnt > 1000) {
            cout << -1;
            break;
        }
        if (!move()) {
            cout << cnt;
            break;
        }

        cnt++;
    }
}