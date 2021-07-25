#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n;
vector<vector<int>> graph;
int answer = 0;

void move(vector<int>& direction) {
	//n*n*5
	vector<vector<int>> copy_graph;
	copy_graph = graph;
	for (auto it : direction) {
		//0은 왼쪽으로 밀기
		if (it == 0) {
			for (int i = 0; i < n; i++) {
				//왼쪽에서 오른쪽으로 스캔
				int tmp = 0;
				queue<int> left;
				for (int j = 0; j < n; j++) {
					if (copy_graph[i][j] != 0 && tmp == 0) {
						tmp = copy_graph[i][j];
					}
					else if (copy_graph[i][j] != 0 && tmp != 0) {
						if (tmp == copy_graph[i][j]) {
							left.push(tmp << 1);
							tmp = 0;
						}
						else {
							left.push(tmp);
							tmp = copy_graph[i][j];
						}
					}
				}
				if (tmp != 0) {
					left.push(tmp);
				}
				for (int j = 0; j < n; j++) {
					if (!left.empty()) {
						copy_graph[i][j] = left.front();
						answer = max(answer, copy_graph[i][j]);
						left.pop();
					}
					else {
						copy_graph[i][j] = 0;
					}
				}
			}
		}
		//1은 오른쪽으로 밀기
		else if (it == 1) {
			for (int i = 0; i < n; i++) {
				//오른쪽에서 왼쪽으로 스캔
				int tmp = 0;
				queue<int> right;
				for (int j = n-1; j >= 0; j--) {
					if (copy_graph[i][j] != 0 && tmp == 0) {
						tmp = copy_graph[i][j];
					}
					else if (copy_graph[i][j] != 0 && tmp != 0) {
						if (tmp == copy_graph[i][j]) {
							right.push(tmp << 1);
							tmp = 0;
						}
						else {
							right.push(tmp);
							tmp = copy_graph[i][j];
						}
					}
				}
				if (tmp != 0) {
					right.push(tmp);
				}
				for (int j = n-1; j >= 0; j--) {
					if (!right.empty()) {
						copy_graph[i][j] = right.front();
						answer = max(answer, copy_graph[i][j]);
						right.pop();
					}
					else {
						copy_graph[i][j] = 0;
					}
				}
			}
		}
		//2는 위로 밀기
		else if (it == 2) {
			for (int j = 0; j < n; j++) {
				//위에서 아래쪽으로 스캔
				int tmp = 0;
				queue<int> up;
				for (int i = 0; i < n; i++) {
					if (copy_graph[i][j] != 0 && tmp == 0) {
						tmp = copy_graph[i][j];
					}
					else if (copy_graph[i][j] != 0 && tmp != 0) {
						if (tmp == copy_graph[i][j]) {
							up.push(tmp << 1);
							tmp = 0;
						}
						else {
							up.push(tmp);
							tmp = copy_graph[i][j];
						}
					}
				}
				if (tmp != 0) {
					up.push(tmp);
				}
				for (int i = 0; i < n; i++) {
					if (!up.empty()) {
						copy_graph[i][j] = up.front();
						answer = max(answer, copy_graph[i][j]);
						up.pop();
					}
					else {
						copy_graph[i][j] = 0;
					}
				}
			}
		}
		//3은 아래로 밀기
		else if (it == 3) {
			for (int j = 0; j < n; j++) {
				//아래에서 위쪽으로 스캔
				int tmp = 0;
				queue<int> down;
				for (int i = n-1; i >= 0; i--) {
					if (copy_graph[i][j] != 0 && tmp == 0) {
						tmp = copy_graph[i][j];
					}
					else if (copy_graph[i][j] != 0 && tmp != 0) {
						if (tmp == copy_graph[i][j]) {
							down.push(tmp << 1);
							tmp = 0;
						}
						else {
							down.push(tmp);
							tmp = copy_graph[i][j];
						}
					}
				}
				if (tmp != 0) {
					down.push(tmp);
				}
				for (int i = n - 1; i >= 0; i--) {
					if (!down.empty()) {
						copy_graph[i][j] = down.front();
						answer = max(answer, copy_graph[i][j]);
						down.pop();
					}
					else {
						copy_graph[i][j] = 0;
					}
				}
			}
		}
	}
	return;
}

void backtrack(int r, vector<int> direction) {
	if (r == 5) {
		move(direction);
		return;
	}
	for (int i = 0; i < 4; i++) {
		vector<int> tmp = direction;
		tmp.push_back(i);
		backtrack(r + 1, tmp);
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n;
	graph = vector<vector<int>>(n, vector<int>(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> graph[i][j];
		}
	}
	//4^5= 1024
	//상하좌우
	vector<int> direction;
	backtrack(0,direction);
	cout << answer;
}