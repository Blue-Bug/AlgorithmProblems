#include<vector>
#include<queue>
using namespace std;

int dir[4][2] = { {1,0}, {0,-1},{0,1},{-1,0} };

int bfs(vector<vector<int>>& maps, int cur_y, int cur_x) {
	int m = maps.size();
	int n = maps.front().size();
	vector<vector<int>> check(m, vector<int>(n, -1));
	check[cur_y][cur_x] = 1;
	queue<pair<int, int>> q;
	q.push({ cur_y,cur_x });

	while (!q.empty()) {
		cur_y = q.front().first;
		cur_x = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int next_y = cur_y + dir[i][0];
			int next_x = cur_x + dir[i][1];
			if (next_y < 0 || next_y >= m) continue;
			if (next_x < 0 || next_x >= n) continue;
			if (check[next_y][next_x] == -1 && maps[next_y][next_x] == 1) {
				check[next_y][next_x] = check[cur_y][cur_x] + 1;
				q.push({ next_y,next_x });
			}
		}
	}
	return check[m - 1][n - 1];
}

int solution(vector<vector<int>> maps) {
	int answer = 0;

	answer = bfs(maps, 0, 0);
	return answer;
}