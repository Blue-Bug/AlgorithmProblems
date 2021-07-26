#include <iostream>

using namespace std;

int dp[501][501];
int files[501];
int sum[501];

int main() {
	int t,n;
	cin >> t;
	while (t--) {
		cin >> n;
		for (int i = 1; i <= n; i++) {
			cin >> files[i];
			sum[i] = sum[i-1] + files[i];
		}
		//dp[i][j] i부터 j까지 합치는 최소 비용
		for (int i = 1; i < n; i++) {
			for (int left = 1; left + i <= n; left++) {
				int right = left + i;
				dp[left][right] = 0x3f3f3f3f;
				//중간 지점을 바꿔가며 dp[left][right]의 최소를 찾음
				for (int mid = left; mid < right; mid++) {
					dp[left][right] = min(dp[left][right], dp[left][mid] + dp[mid + 1][right] + sum[right] - sum[left-1]);
				}
			}
		}
		cout << dp[1][n] << '\n';
	}
}