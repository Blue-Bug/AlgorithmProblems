#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m, k;
int nutrient[11][11];
vector<vector<int>>ground(11, vector<int>(11, 5));
//first는 나이 second는 개수
vector<pair<int, int>> trees[11][11];
int dir[8][2] = { {0,1},{1,0},{-1,0},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1} };

void spring_summer() {
	vector<pair<int, int>> newtrees[11][11];
	vector<vector<int>> summer(11, vector<int>(11, 0));

	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < n + 1; j++) {
			for (auto it : trees[i][j]) {
				int cost = it.first * it.second;
				if (ground[i][j] < cost) {
					if ((ground[i][j] / it.first) == 0) {
						summer[i][j] += ((it.first / 2) * it.second);
					}
					else {
						newtrees[i][j].push_back({ it.first + 1, (ground[i][j] / it.first) });
						summer[i][j] += (((it.first / 2) * (it.second - (ground[i][j] / it.first))));
						ground[i][j] -= (it.first * (ground[i][j] / it.first));
					}
				}
				else {
					ground[i][j] -= cost;
					newtrees[i][j].push_back({ it.first + 1,it.second });
				}

			}
			trees[i][j] = newtrees[i][j];
		}
	}
	//N^2 * M
	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < n + 1; j++) {
			ground[i][j] += summer[i][j];
		}
	}
}

void fall() {
	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < n + 1; j++) {
			for (auto it : trees[i][j]) {
				if (it.first % 5 == 0) {
					for (int p = 0; p < 8; p++) {
						int nextRow = i + dir[p][0];
						int nextCol = j + dir[p][1];
						if (nextRow < 1 || nextRow > n) continue;
						if (nextCol < 1 || nextCol > n) continue;
						if (!trees[nextRow][nextCol].empty() && trees[nextRow][nextCol][0].first == 1) {
							trees[nextRow][nextCol][0].second+= it.second;
						}
						else {
							trees[nextRow][nextCol].insert(trees[nextRow][nextCol].begin(), { 1,it.second });
						}
					}
				}
			}
		}
	}
}

void winter() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			ground[i][j] += nutrient[i][j];
		}
	}
}

void fourSeasons() {
	spring_summer();
	fall();
	winter();
}

int main() {
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> nutrient[i][j];
		}
	}

	int x, y, z;
	for (int i = 0; i < m; i++) {
		cin >> x >> y >> z;
		trees[x][y].push_back({ z,1 });
	}

	while (k--) {
		fourSeasons();
	}

	int answer = 0;
	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < n + 1; j++) {
			for (auto it : trees[i][j]) {
				answer += it.second;
			}
		}
	}
	cout << answer;
}