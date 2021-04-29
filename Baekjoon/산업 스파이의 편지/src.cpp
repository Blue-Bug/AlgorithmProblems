#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <unordered_set>
using namespace std;
bool prime[10000000]{ false };
unordered_set<int> mSet;
bool check[7]{ false };

void find_prime(string comb, string tmp, int n, int r, int MAX) {
	if (n == r) {
		if (!prime[stoi(comb)]) {
			mSet.insert(stoi(comb));
		}
		return;
	}
	for (int i = 0; i < MAX; i++) {
		if (check[i]) continue;
		check[i] = true;
		comb += tmp[i];
		find_prime(comb, tmp, n, r + 1, MAX);
		comb = comb.substr(0, comb.size() - 1);
		check[i] = false;
	}
}

int main() {
	int c;
	cin >> c;
	prime[0] = true;
	prime[1] = true;
	for (int i = 2; i * i < 10000000; i++) {
		if (!prime[i]) {
			for (int j = i * i; j < 10000000; j += i) {
				prime[j] = true;
			}
		}
	}
	for (int i = 0; i < c; i++) {
		string tmp;
		cin >> tmp;
		for (int j = 1; j <= tmp.size(); j++) {
			find_prime("", tmp, j, 0, tmp.size());
		}
		cout << mSet.size() << '\n';
		mSet.clear();
		memset(check, false, sizeof(check));
	}
}