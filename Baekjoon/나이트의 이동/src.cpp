#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int dir[8][2] = { {2,-1},{2,1},{1,-2},{1,2},{-2,-1},{-2,1},{-1,-2},{-1,2} };
bool isRightPos(int row, int col, int chess_size) {
	if (row >= 0 && row < chess_size && col >= 0 && col < chess_size) {
		return true;
	}
	return false;
}

int bfs(int chess_size,pair<int,int> curKnight, pair<int,int> targetKnight) {
	queue<pair<pair<int, int>,int>> q;
	vector<vector<bool>> visited(300, vector<bool>(300, false));
	q.push({ curKnight,0 });

	while (!q.empty()) {
		int row = q.front().first.first;
		int col = q.front().first.second;
		int cnt = q.front().second;
		q.pop();

		if (targetKnight.first == row&&
			targetKnight.second == col) {
			return cnt;
		}
		if (visited[row][col]) {
			continue;
		}
		visited[row][col] = true;
		for (int i = 0; i < 8; i++) {
			int next_row = row + dir[i][0];
			int next_col = col + dir[i][1];
			if (isRightPos(next_row, next_col, chess_size) && !visited[next_row][next_col]) {
				q.push({ {next_row,next_col},cnt + 1 });
			}
		}
	}
	return 0;
}


int main() {
	int t;
	cin >> t;
	while (t--) {
		int chess_size = 0;
		pair<int, int> curKnight;
		pair<int, int> targetKnight;
		cin >> chess_size;
		cin >> curKnight.first >> curKnight.second;
		cin >> targetKnight.first >> targetKnight.second;

		cout << bfs(chess_size,curKnight, targetKnight) << '\n';
	}
}