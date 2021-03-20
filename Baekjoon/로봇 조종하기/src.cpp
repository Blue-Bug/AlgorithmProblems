#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int dp[1004][1004];
int dp_l[1004][1004];
int dp_r[1004][1004];
int n, m;

void solution(vector<vector<int>> &mars) {
	//재귀호출
	dp[0][0] = mars[0][0];
	for (int i = 1; i < m; i++) {
		dp[0][i] += dp[0][i - 1] + mars[0][i];
	}

	int idx = 0;
	while (++idx < n) {
		//아래로 내려와서 왼쪽 오른쪽 감
		for (int x = 0; x < m; x++) {
			dp_l[idx][x] = dp[idx - 1][x] + mars[idx][x];
			dp_r[idx][x] = dp[idx - 1][x] + mars[idx][x];
		}
		//왼쪽으로 감
		for (int j = m - 2; j >= 0; j--) {
			if (dp_l[idx][j] < dp_l[idx][j + 1] + mars[idx][j]) {
				dp_l[idx][j] = dp_l[idx][j + 1] + mars[idx][j];
			}
		}
		//오른쪽으로 감
		for (int j = 1; j < m; j++) {
			if (dp_r[idx][j] < dp_r[idx][j - 1] + mars[idx][j]) {
				dp_r[idx][j] = dp_r[idx][j - 1] + mars[idx][j];
			}
		}
		for (int j = 0; j < m; j++) {
			dp[idx][j] = max(dp_l[idx][j], dp_r[idx][j]);
		}
	}
}


int main() {
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> n >> m;
	vector<vector<int>> mars(n, vector<int>(m, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> mars[i][j];
		}
	}
	solution(mars);
	cout << dp[n-1][m-1];
}