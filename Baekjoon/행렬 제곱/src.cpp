#include <iostream>
#include <vector>
using namespace std;

#define ll long long

ll n, b;
vector<vector<ll>> a(5, vector<ll>(5, 0));
vector<vector<ll>> c(5, vector<ll>(5, 0));
void caMerge() {
	vector<vector<ll>> d(5,vector<ll>(5,0));
	for (ll i = 0; i < n; i++) {
		for (ll j = 0; j < n; j++) {
			for (ll t = 0; t < n; t++) {
				d[i][j] += ((c[i][t] % 1000) * (a[t][j] % 1000)) % 1000;
			}
			d[i][j] %= 1000;
		}
	}
	for (ll i = 0; i < n; i++) {
		for (ll j = 0; j < n; j++) {
			c[i][j] = d[i][j];
		}
	}
	return;
}
void ccMerge() {
	vector<vector<ll>> d(5, vector<ll>(5, 0));
	for (ll i = 0; i < n; i++) {
		for (ll j = 0; j < n; j++) {
			for (ll t = 0; t < n; t++) {
				d[i][j] += ((c[i][t] % 1000) * (c[t][j] % 1000)) % 1000;
			}
			d[i][j] %= 1000;
		}
	}
	for (ll i = 0; i < n; i++) {
		for (ll j = 0; j < n; j++) {
			c[i][j] = d[i][j];
		}
	}
}
void merge(ll cur) {
	if (cur == 1) {
		caMerge();
		return;
	}
	if (cur % 2 == 1) {
		merge((cur - 1) / 2);
		caMerge();
		if (cur == b) return;
		ccMerge();
		return;
	}
	else {
		merge(cur / 2);
		if (cur == b) return;
		ccMerge();
		return;
	}
}

void printVec() {
	for (ll i = 0; i < n; i++) {
		for (ll j = 0; j < n; j++) {
			cout << c[i][j] %1000 << ' ';
		}
		cout << '\n';
	}
}

int main() {
	cin >> n >> b;
	for (ll i = 0; i < n; i++) {
		for (ll j = 0; j < n; j++) {
			cin >> a[i][j];
			c[i][j] = a[i][j];
		}
	}
	if (b == 1) {
		printVec();
		return 0;
	}
	if (b == 2) {
		caMerge();
		printVec();
		return 0;
	}
	merge(b);
	printVec();
}