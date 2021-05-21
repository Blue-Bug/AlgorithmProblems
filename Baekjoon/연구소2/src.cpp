#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct node {
	int row, col, cnt;
};
int n, m, mmax = 987654321;
int space = 0;
int dir[4][2] = { {0,1},{1,0},{-1,0},{0,-1} };
queue<node> q;
vector<vector<int>> graph;
vector<pair<int, int>> comb;

int cnt_area(vector<vector<int>>& graph) {
	bool check[50][50]{ false };
	int space_copy = space;
	int result = 0;
	while (!q.empty()) {
		int row = q.front().row;
		int col = q.front().col;
		int cnt = q.front().cnt;
		q.pop();

		if (result < cnt) {
			result = cnt;
		}
		for (int i = 0; i < 4; i++) {
			int nrow = row + dir[i][0];
			int ncol = col + dir[i][1];
			if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < n
				&& graph[nrow][ncol] == 0 && !check[nrow][ncol]) {
				check[nrow][ncol] = true;
				q.push({ nrow,ncol,cnt + 1 });
				space_copy--;
			}
		}
	}
	if (space_copy == 0) {
		return result;
	}
	else {
		return 987654321;
	}
}

void make_wall(int start, int pick, vector<bool>& check, vector<vector<int>>& graph) {
	if (pick == m) {
		for (int i = 0; i < check.size(); i++) {
			if (check[i]) {
				q.push({ comb[i].first,comb[i].second,0 });
			}
		}
		int res = cnt_area(graph);
		if (mmax > res) {
			mmax = res;
		}
		return;
	}
	for (int i = start; i < comb.size(); i++) {
		if (graph[comb[i].first][comb[i].second] == 0) {
			graph[comb[i].first][comb[i].second] = 2;
			check[i] = true;
			make_wall(i, pick + 1, check, graph);
			check[i] = false;
			graph[comb[i].first][comb[i].second] = 0;
		}
	}
}

int main() {
	cin >> n >> m;
	graph = vector<vector<int>>(n, vector<int>(n, 0));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> graph[i][j];
			if (graph[i][j] == 0) {
				space++;
			}
			if (graph[i][j] == 2) {
				graph[i][j] = 0;
				space++;
				comb.push_back({ i,j });
			}
		}
	}
	space -= m;
	vector<bool> check(comb.size(), false);
	make_wall(0, 0, check, graph);
	if (mmax != 987654321) {
		cout << mmax;
	}
	else {
		cout << -1;
	}
}