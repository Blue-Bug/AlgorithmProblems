#include <iostream>
#include <set>
using namespace std;

int t, k;
multiset<int> mset;

int main() {
	cin >> t;
	while (t--) {
		cin >> k;
		mset.clear();
		for (int i = 0; i < k; i++) {
			char command;
			int val;
			cin >> command >> val;
			if (command == 'I') {
				mset.insert(val);
			}
			else if (command == 'D') {
				if (mset.empty()) {
					continue;
				}
				if (val == 1) {
					//최대 삭제
					auto it = mset.end();
					mset.erase(--it);
				}
				else if (val == -1) {
					//최소 삭제
					mset.erase(mset.begin());
				}
			}
		}
		if (mset.empty()) {
			cout << "EMPTY" << '\n';
		}
		else {
			//최대 최소
			cout << *mset.rbegin() << ' ';
			cout << *mset.begin() << '\n';
		}
	}
}