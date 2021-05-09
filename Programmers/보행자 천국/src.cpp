#include <vector>
using namespace std;

int MOD = 20170805;
//0은 오른쪽,1은 아래

int solution(int m, int n, vector<vector<int>> city_map) {
	long long dp[500][500][2]{ 0 };
	for (int i = 1; i < m; i++) {
		if (city_map[i][0] == 1) break;
		dp[i][0][0] = 1;
	}
	for (int j = 1; j < n; j++) {
		if (city_map[0][j] == 1) break;
		dp[0][j][1] = 1;
	}
	for (int i = 1; i < m; i++) {
		for (int j = 1; j < n; j++) {
			if (city_map[i][j] == 1) continue;
			if (city_map[i - 1][j] == 2) {
				//한방향으로만 가야됨
				dp[i][j][0] = (dp[i][j][0] + dp[i - 1][j][0]) % MOD;
			}
			if (city_map[i][j - 1] == 2) {
				dp[i][j][1] = (dp[i][j][1] + dp[i][j - 1][1]) % MOD;
			}
			if (city_map[i - 1][j] == 0) {
				dp[i][j][0] = (dp[i][j][0] + dp[i - 1][j][0] + dp[i - 1][j][1]) % MOD;
			}
			if (city_map[i][j - 1] == 0) {
				dp[i][j][1] = (dp[i][j][1] + dp[i][j - 1][0] + dp[i][j - 1][1]) % MOD;
			}
		}
	}
	return (dp[m - 1][n - 1][0] + dp[m - 1][n - 1][1]) % MOD;
}