#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int w, h, answer = 987654231;

int dir[4][2] = { {0,1},{1,0},{-1,0},{0,-1} };
char graph[20][20];
vector<vector<int>> posVec;
vector<pair<int,int>> posVec2;
vector<vector<int>> distVec;

struct node {
	int row, col, cnt;
};

bool bfs(pair<int, int> start) {
	queue<node> q;
	q.push({ start.first,start.second,0 });
	bool check[20][20]{ false };

	bool flag = true;
	while (!q.empty()) {
		node cur = q.front();
		q.pop();
		if (check[cur.row][cur.col]) continue;
		check[cur.row][cur.col] = true;

		for (int i = 0; i < 4; i++) {
			int nextRow = cur.row + dir[i][0];
			int nextCol = cur.col + dir[i][1];
			if (nextRow < 0 || nextRow >= h) continue;
			if (nextCol < 0 || nextCol >= w) continue;
			if (graph[nextRow][nextCol] == 'x') continue;
			
			if (!check[nextRow][nextCol]) {
				q.push({ nextRow,nextCol,cur.cnt + 1 });
				if (graph[nextRow][nextCol] == '*') {
					flag = false;
					int startIdx = posVec[start.first][start.second];
					int endIdx = posVec[nextRow][nextCol];
					distVec[startIdx][endIdx] = cur.cnt + 1;
					distVec[endIdx][startIdx] = cur.cnt + 1;
				}
			}
		}
	}
	if (flag) {
		return false;
	}
	return true;
}

void backtrack(int n, int k,vector<int>& pick) {
	if (n == k) {
		int result = 0;
		int prev = 0;
		for (int i = 0; i < pick.size(); i++) {
			result += distVec[prev][pick[i]];
			prev = pick[i];
		}
		answer = min(answer, result);
		return;
	}
	for (int i = k; i < n; i++) {
		swap(pick[k], pick[i]);
		backtrack(n, k + 1, pick);
		swap(pick[k], pick[i]);
	}
}

int main() {
	while (1) {
		cin >> w >> h;
		posVec = vector<vector<int>>(h, vector<int>(w));
		int index = 1;
		if (w == 0 && h == 0) break;
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				cin >> graph[i][j];
				if (graph[i][j] == 'o') {
					graph[i][j] = '.';
					posVec[i][j] = 0;
					posVec2.insert(posVec2.begin(),{ i, j });
				}
				if (graph[i][j] == '*') {
					posVec[i][j] = index++;
					posVec2.push_back({ i, j });
				}
			}
		}
		if (index == 1) {
			cout << 0 << '\n';
			continue;
		}
		distVec = vector<vector<int>>(posVec2.size(), vector<int>(posVec2.size()));
		for (int i = 0; i < index; i++) {
			if (!bfs(posVec2[i])) {
				answer = -1;
			}
		}

		vector<int> pick(index - 1);
		for (int i = 0; i < index - 1; i++) {
			pick[i] = i+1;
		}
		backtrack(index-1, 0,pick);
		cout << answer << '\n';
		answer = 987654321;
		posVec2.clear();
	}
}