#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m;
int direction, speed;
bool moveFlag = false;
vector<vector<int>> graph;
vector<pair<int, int>> removePos;
queue<int> copyQ;
queue<int> copyQ2;
int prevBall, sameCnt = 1;
int row , col;
int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
int answer = 0;

void move(int moveDir,int cnt,int mode) {
	while (cnt--) {
		row += dir[moveDir][0];
		col += dir[moveDir][1];

		//돌면서 복사함
		if (mode == 2) {
			if (graph[row][col] == 0) {
				continue;
			}
			copyQ.push(graph[row][col]);
			graph[row][col] = 0;
		}

		//복사한거 넣기
		if (mode == 3) {
			if (!copyQ.empty()) {
				graph[row][col] = copyQ.front();
				copyQ.pop();
			}
		}
		
		//4개 이상 터뜨리는거
		if (mode == 1) {
			if (graph[row][col] == prevBall && prevBall != 0) {
				removePos.emplace_back(row, col);
				sameCnt++;
			}
			else {
				if (sameCnt >= 4) {
					//이전꺼를 다 지움
					for (auto it : removePos) {
						answer += graph[it.first][it.second];
						graph[it.first][it.second] = 0;
					}
					moveFlag = true;
				}

				sameCnt = 1;
				removePos.clear();
				prevBall = graph[row][col];
				removePos.emplace_back(row, col);
			}
		}
		
	}
}

void throwIce() {
	row = col = n / 2;
	for (int i = 0; i < speed; i++) {
		row += dir[direction][0];
		col += dir[direction][1];
		graph[row][col] = 0;
	}

}

void clearQueue(queue<int> &q) {
	queue<int> emptyQ;
	swap(q, emptyQ);
}

void moveLower(int mode) {
	row = col = n / 2;
	int cnt = 1;
	while (cnt <= n) {
		if (cnt == n) {
			cnt--;
			move(2, cnt,mode);
			return;
		}
		move(2, cnt,mode);
		move(1, cnt++,mode);
		move(3, cnt,mode);
		move(0, cnt++,mode);
	}
}

int main() {
	cin >> n >> m;
	graph = vector<vector<int>>(n, vector<int>(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> graph[i][j];
		}
	}

	for (int i = 0; i < m; i++) {
		cin >> direction >> speed;
		direction--;
		throwIce();
		moveLower(2);
		moveLower(3);

		prevBall = graph[n / 2][n / 2];
		while (1) {
			moveLower(1);
			if (!moveFlag) break;
			moveLower(2);
			moveLower(3);
			moveFlag = false;
		}
		//복사 해옴
		moveLower(2);
		int cnt = 0;
		int prevCur = copyQ.front();
		while (!copyQ.empty()) {
			int cur = copyQ.front();
			copyQ.pop();
			if (prevCur == cur) {
				cnt++;
				if (copyQ.empty()) {
					copyQ2.push(cnt);
					copyQ2.push(prevCur);
				}
			}
			else {
				copyQ2.push(cnt);
				copyQ2.push(prevCur);
				prevCur = cur;
				cnt = 1;
				if (copyQ.empty()) {
					copyQ2.push(cnt);
					copyQ2.push(prevCur);
				}
			}
		}
		copyQ = copyQ2;
		
		clearQueue(copyQ2);
		moveLower(3);
		clearQueue(copyQ);
	}
	cout << answer;
}