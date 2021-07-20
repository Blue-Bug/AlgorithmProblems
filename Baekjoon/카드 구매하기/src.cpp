#include <iostream>
#include <vector>
using namespace std;

int n, tmp;
int dp[1001]{ 0 };

vector<int> v(1001);
void myFunc(int remain) {
	if (remain == 0) {
		return;
	}
	
}
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> v[i];
	}
	//dp테이블을 분할해서 dp[1]부터 차례대로 채워간다.
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			dp[i] = max(dp[i - j] + v[j], dp[i]);
		}
	}
	cout << dp[n];
}