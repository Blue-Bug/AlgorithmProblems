#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

int n, m;
vector<vector<int>> graph;
vector<vector<bool>>check;
set<pair<int,int>> insideAir;
set<pair<int,int>> onePos;
int dir[4][2] = { {0,1},{1,0},{-1,0},{0,-1} };

void bfs(int row, int col) {
	queue<pair<int, int>> q;
	q.push({ row,col });
	vector<pair<int, int>> tmp;
	bool flag = true;
	while (!q.empty()) {
		pair<int, int> cur = q.front();
		q.pop();

		if (check[cur.first][cur.second]) continue;
		check[cur.first][cur.second] = true;

		tmp.push_back({ cur.first, cur.second });
		if (cur.first == 0 || cur.first == n - 1
			|| cur.second == 0 || cur.second == m - 1) {
			flag = false;
		}
		for (int i = 0; i < 4; i++) {
			int nextRow = cur.first + dir[i][0];
			int nextCol = cur.second + dir[i][1];

			if (nextRow < 0 || nextRow >= n) continue;
			if (nextCol < 0 || nextCol >= m) continue;
			if (graph[nextRow][nextCol] == 0) {
				q.push({ nextRow,nextCol });
			}
		}
	}
	if(flag){
		for (auto it : tmp) {
			insideAir.insert({ it.first,it.second });
		}
	}
}

bool checkAir(int row, int col) {
	int cnt = 0;
	for (int i = 0; i < 4; i++) {
		int nextRow = row + dir[i][0];
		int nextCol = col + dir[i][1];
		if (nextRow < 0 || nextRow >= n) continue;
		if (nextCol < 0 || nextCol >= m) continue;
		
		if (graph[nextRow][nextCol] == 0 && insideAir.find({ nextRow,nextCol }) == insideAir.end()) {
			cnt++;
		}
	}
	if (cnt >= 2) {
		return true;
	}
	return false;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n >> m;
	graph = vector<vector<int>>(n, vector<int>(m, 0));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> graph[i][j];
			if (graph[i][j] == 1) {
				onePos.insert({i, j});
			}
		}
	}
	int answer = 0;

	
	while (!onePos.empty()) {
		//치즈 내부 공간 찾기
		check = vector<vector<bool>>(n, vector<bool>(m, false));
		for (int i = 1; i < n - 1; i++) {
			for (int j = 1; j < m - 1; j++) {
				if (graph[i][j] == 0 && !check[i][j]) {
					bfs(i, j);
				}
			}
		}

		vector<pair<int, int>> removePos;
		for (auto it : onePos) {
			if (checkAir(it.first, it.second)) {
				removePos.push_back({ it.first, it.second });
			}
		}

		for (auto it : removePos) {
			graph[it.first][it.second] = 0;
			onePos.erase({it.first,it.second});
		}
		insideAir.clear();
		answer++;
	}
	cout << answer;
}