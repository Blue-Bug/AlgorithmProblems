#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n,tmp;
	cin >> n;
	vector<int> numbers;

	for (int i = 0; i < n; i++) {
		cin >> tmp;
		if (numbers.empty()) {
			numbers.push_back(tmp);
		}
		else if (tmp > numbers.back()) {
			numbers.push_back(tmp);
		}
		else {
			auto it = lower_bound(numbers.begin(), numbers.end(),tmp);
			*it = tmp;
		}
	}
	cout << numbers.size();
}