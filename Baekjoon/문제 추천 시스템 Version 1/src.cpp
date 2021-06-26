#include <iostream>
#include <string>
#include <set>
using namespace std;

auto cmp = [](const pair<int, int> & left, const pair<int, int> & right)
{
	if (left.second == right.second) {
		return left.first > right.first;
	}
	return left.second > right.second;
};

struct my_compare {
	bool operator()(const pair<int, int> left, const pair<int, int> right) const{
		if (left.second == right.second) {
			return left.first > right.first;
		}
		return left.second > right.second;
	};
};
int n,m;

int main() {
	multiset<pair<int, int>, my_compare> mset;
	cin >> n;
	int p, l;
	for (int i = 0; i < n; i++){
		cin >> p >> l;
		mset.emplace( p, l );
	}
	cin >> m;
	string command;
	for (int i = 0; i < m; i++) {
		cin >> command;
		if (command == "recommend") {
			cin >> p;
			if (p == 1) {
				cout << (*mset.begin()).first << '\n';
			}
			else if (p == -1) {
				cout << (*mset.rbegin()).first << '\n';
			}
		}
		else if (command == "add") {
			cin >> p >> l;
			mset.emplace( p, l );
		}
		else if (command == "solved") {
			cin >> p;
			for (int i = 1; i < 101; i++) {
				mset.erase({ p, i});
			}
		}
	}
}