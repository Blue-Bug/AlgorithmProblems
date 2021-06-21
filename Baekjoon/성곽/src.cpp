#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n, m, roomMAX = 0;
vector<vector<int>> graph;
vector<vector<int>> check;
vector<pair<int, int>> roomRank;
int dir[4][2] = { {0,-1},{-1,0},{0,1},{1,0} };
int wall[4] = { 1,2,4,8 };

bool cmp(pair<int, int> a, pair<int, int> b) {
	return a.second > b.second;
}

bool bfs(int row, int col, int idx) {
	if (check[row][col] != 0) {
		return false;
	}
	int cnt = 0;
	queue<pair<int, int>> q;
	q.emplace(row, col);

	while (!q.empty()) {
		pair<int, int> cur = q.front();
		q.pop();
		if (check[cur.first][cur.second] != 0) continue;
		check[cur.first][cur.second] = idx;
		cnt++;
		for (int i = 0; i < 4; i++) {
			if ((graph[cur.first][cur.second] & wall[i]) == wall[i]) continue;
			int nextRow = cur.first + dir[i][0];
			int nextCol = cur.second + dir[i][1];

			if (check[nextRow][nextCol] == 0) {
				q.emplace(nextRow, nextCol);
			}
		}
	}
	roomRank.emplace_back(idx, cnt);
	return true;
}

void cntRoom() {
	int idx = 1;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (bfs(i, j, idx)) {
				idx++;
			}
		}
	}
	sort(roomRank.begin(), roomRank.end(), cmp);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n >> m;

	graph = vector<vector<int>>(m, vector<int>(n));
	check = vector<vector<int>>(m, vector<int>(n));

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cin >> graph[i][j];
		}
	}

	cntRoom();

	cout << roomRank.size() << '\n';
	cout << roomRank.front().second << '\n';
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (graph[i][j] > 0) {
				for (int k = 0; k < 4; k++) {
					if ((graph[i][j] & wall[k]) == wall[k]) {
						int nextRow = i + dir[k][0];
						int nextCol = j + dir[k][1];
						
						if (nextRow < 0 || nextRow >= m) continue;
						if (nextCol < 0 || nextCol >= n) continue;
						int mergeIdx = check[nextRow][nextCol];
						int curIdx = check[i][j];
						if (mergeIdx == curIdx) continue;
						int cmpVal = 0;
						for (int l = 0; l < roomRank.size(); l++) {
							if (roomRank[l].first == curIdx) {
								cmpVal += roomRank[l].second;
							}
							if (roomRank[l].first == mergeIdx) {
								cmpVal += roomRank[l].second;
							}
						}
						if (roomMAX < cmpVal) {
							roomMAX = cmpVal;
						}
					}
				}
			}
		}
	}
	cout << roomMAX;
}