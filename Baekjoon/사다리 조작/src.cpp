#include <iostream>
#include <vector>

using namespace std;


int n, m, h;
bool ladder[271][11]{ false };

bool testLadder() {
	for (int col = 1; col <= n; col++) {
		int startCol = col;
		for (int row = 1; row <= h; row++) {
			if (ladder[row][startCol]) startCol++;
			else if (ladder[row][startCol - 1]) startCol--;
		}
		if (startCol != col) {
			return false;
		}
	}
	return true;
}

bool backtrack(int end, int cur, int idx) {
	if (end == cur) {
		return testLadder();
	}
	
	for (int i = idx; i <= h; i++) {
		//가로 선
		for (int j = 1; j < n; j++) {
			//어느 세로 선에 넣을 것인가
			if (ladder[i][j + 1] || ladder[i][j - 1] || ladder[i][j]) {
				continue;
			}
			
			ladder[i][j] = true;
			if (backtrack(end, cur + 1, i)) {
				return true;
			}
			ladder[i][j] = false;
		}
	}
	return false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> m >> h;

	int a, b;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		//a 가로선에서 b와 b+1 세로선이 연결됐다.
		ladder[a][b] = true;
	}
	if (m == 0 || testLadder()) {
		cout << 0;
		return 0;
	}

	for (int i = 1; i <= 3; i++) {
		//고를 수 있는 개수
		if (backtrack(i, 0, 1)) {
			cout << i;
			return 0;
		}
	}

	cout << -1;
	return 0;
}