#include <iostream>
#include <vector>
#include <string>
using namespace std;

int n, k, answer = 0;
int knownAlpha = 0;
vector<string> strVec;

int matchString() {
	int cnt = 0;
	for (auto str : strVec) {
		for (int i = 0; i <= str.size(); i++) {
			if (i == str.size()) {
				cnt++;
				break;
			}
			else if ((knownAlpha & (1 << (str[i]-97))) == 0) break;
		}
	}
	return cnt;
}

void backtrack(int end, int cur, int idx) {
	if (end == cur) {
		//문자열 체크
		answer = max(answer, matchString());
		return;
	}
	for (int i = idx; i < 26; i++) {
		int tmp = 1 << i;
		if ((knownAlpha & tmp) == tmp) {
			continue;
		}

		knownAlpha |= tmp;
		backtrack(end, cur + 1, i+1);
		knownAlpha ^= tmp;
	}
}

int main() {
	cin >> n >> k;
	if (k < 5) {
		cout << 0;
		return 0;
	}
	//a,n,t,i,c
	knownAlpha += (1 << 'a' - 97);
	knownAlpha += (1 << 'n' - 97);
	knownAlpha += (1 << 't' - 97);
	knownAlpha += (1 << 'i' - 97);
	knownAlpha += (1 << 'c' - 97);
	
	k -= 5;

	for (int i = 0; i < n; i++) {
		string tmp;
		cin >> tmp;
		tmp = tmp.substr(4);
		tmp = tmp.substr(0, tmp.size() - 4);
		strVec.push_back(tmp);
	}

	vector<bool> check(26,false);
	backtrack(k, 0, 0);
	cout << answer;
}