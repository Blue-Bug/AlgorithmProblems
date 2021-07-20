#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n;
	cin >> n;
	vector<int> v[10001];
	priority_queue<int> q;
	for (int i = 0; i < n; i++) {
		int day, pay;
		cin >> pay >> day;
		v[day].push_back(pay);
	} 
	int answer = 0;
	for (int i = 10000; i > 0; i--) {
		for (auto pay : v[i]) {
			q.push(pay);
		}
		if (!q.empty()) {
			answer += q.top();
			q.pop();
		}
	}
	cout << answer;
}