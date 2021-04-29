#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int main() {
    int n;
    vector<vector<int>>dp(4, vector<int>(3, 0));
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> dp[2][j];
            dp[3][j] = dp[2][j];
            dp[2][j] += max(dp[0][1], (j == 1) ? max(dp[0][0], dp[0][2]) : dp[0][j]);
            dp[3][j] += min(dp[1][1], (j == 1) ? min(dp[1][0], dp[1][2]) : dp[1][j]);
        }
        dp[0].assign(dp[2].begin(), dp[2].end());
        dp[1].assign(dp[3].begin(), dp[3].end());
    }
    cout << max(dp[0][0], max(dp[0][1], dp[0][2])) << ' '
        << min(dp[1][0], min(dp[1][1], dp[1][2]));
}