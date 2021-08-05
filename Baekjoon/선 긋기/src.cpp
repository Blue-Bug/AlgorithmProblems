#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp(pair<int, int> a, pair<int, int> b) {
	return a.first < b.first;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n;
	cin >> n;
	vector<pair<int, int>> lines;
	int a, b;
	for (int i = 0; i < n; i++) {
		cin >> a >> b;
		lines.push_back({ a,b });
	}
	sort(lines.begin(), lines.end());
	int first = lines[0].first, last = lines[0].second, answer = 0;
	for (int i = 1; i <= n; i++) {
		if (i == n) {
			answer += (last - first);
		}
		else {
			if (lines[i].first <= last) {
				//이어질 수 있음
				last = max(last,lines[i].second);
			}
			else {
				//이어질 수 없음
				answer += (last - first);
				first = lines[i].first;
				last = lines[i].second;
			}
		}
	}
	cout << answer;
	
}