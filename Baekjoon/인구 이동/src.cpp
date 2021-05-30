#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <unordered_map>
using namespace std;

struct node {
	int row, col, part;
};
struct parts {
	int val, cnt;
};
int n, l, r, answer = 0;
int dir[4][2] = { {0,1},{0,-1},{1,0},{-1,0} };
vector<vector<int>> world;
queue<node> q;

bool bfs(vector<vector<int>>& check, unordered_map<int, parts>& part_map) {
	bool flag = false;

	while (!q.empty()) {
		node cur = q.front();
		q.pop();

		if (check[cur.row][cur.col] != 0) continue;

		for (int i = 0; i < 4; i++) {
			int nextRow = cur.row + dir[i][0];
			int nextCol = cur.col + dir[i][1];
			if (nextRow >= 0 && nextRow < n && nextCol >= 0 && nextCol < n
				&& check[nextRow][nextCol] == 0) {
				int compVal = abs(world[nextRow][nextCol] - world[cur.row][cur.col]);
				if (compVal >= l && compVal <= r) {
					flag = true;
					q.push({ nextRow,nextCol,cur.part });
				}
			}
		}
		if (flag) {
			check[cur.row][cur.col] = cur.part;
			part_map[cur.part].val += world[cur.row][cur.col];
			part_map[cur.part].cnt++;
		}
	}

	if (flag) {
		return true;
	}
	return false;
}

int main() {
	cin >> n >> l >> r;
	world = vector<vector<int>>(n, vector<int>(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> world[i][j];
		}
	}
	while (1) {
		vector<vector<int>> check(n, vector<int>(n, 0));
		unordered_map<int, parts> part_map;
		int cnt = 0;
		int part = 1;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				q.push({ i, j, part++ });
				if (!bfs(check, part_map)) {
					cnt++;
				}
			}
		}
		if (cnt == n * n) {
			break;
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (check[i][j] != 0) {
					parts tmp = part_map[check[i][j]];
					world[i][j] = tmp.val / tmp.cnt;
				}
			}
		}
		answer++;
	}
	cout << answer;
}