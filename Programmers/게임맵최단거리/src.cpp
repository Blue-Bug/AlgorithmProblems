#include<vector>
#include<queue>
using namespace std;

int dir[4][2] = { {1,0}, {0,-1},{0,1},{-1,0} };

bool isRightPos(int y, int x, int m, int n, vector<vector<int>> &maps) {
	if (x < n && y < m && x >= 0 && y >= 0) {
		if (maps[y][x] == 1) {
			return true;
		}
	}
	return false;
}

int bfs(vector<vector<int>> &maps,int cur_y,int cur_x) {
	int m = maps.size();
	int n = maps.front().size();
	vector<vector<int>> check(m, vector<int>(n, -1));
	check[cur_y][cur_x] = 1;
	queue<pair<int, int>> q;
	q.push({ cur_y,cur_x });

	while (!q.empty()) {
		//위 왼쪽 오른쪽 아래
		cur_y = q.front().first;
		cur_x = q.front().second;
		q.pop();

		int next_y[4] = { cur_y + dir[0][0], cur_y + dir[1][0], cur_y + dir[2][0], cur_y + dir[3][0]};
		int next_x[4] = { cur_x + dir[0][1], cur_x + dir[1][1], cur_x + dir[2][1], cur_x + dir[3][1]};

		for (int i = 0; i < 4; i++) {
			if (isRightPos(next_y[i], next_x[i],m,n, maps)) {
				if (check[next_y[i]][next_x[i]] == -1) {
					check[next_y[i]][next_x[i]] = check[cur_y][cur_x] + 1;
					q.push({ next_y[i],next_x[i] });
				}
			}
		}
	}
	return check[m - 1][n - 1];
}

int solution(vector<vector<int> > maps) {
	int answer = 0;
	
	answer = bfs(maps,0,0);
	return answer;
}

int main() {
	solution({ {1,0,1,1,1 }, { 1,0,1,0,1 }, { 1,0,1,1,1 }, { 1,1,1,0,1 }, { 0,0,0,0,1 } });
}