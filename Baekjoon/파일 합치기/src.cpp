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
		//dp[i][j] i���� j���� ��ġ�� �ּ� ���
		for (int i = 1; i < n; i++) {
			for (int left = 1; left + i <= n; left++) {
				int right = left + i;
				dp[left][right] = 0x3f3f3f3f;
				//�߰� ������ �ٲ㰡�� dp[left][right]�� �ּҸ� ã��
				for (int mid = left; mid < right; mid++) {
					dp[left][right] = min(dp[left][right], dp[left][mid] + dp[mid + 1][right] + sum[right] - sum[left-1]);
				}
			}
		}
		cout << dp[1][n] << '\n';
	}
}