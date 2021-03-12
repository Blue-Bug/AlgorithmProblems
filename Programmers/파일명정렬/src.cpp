#include <string>
#include <vector>
#include <algorithm>
using namespace std;
vector<string> processHNT(string a) {
	vector<string> HNT;
	string tmp = "";
	int idx = 0;
	for (; idx < a.size(); idx++) {
		if (a[idx] < '0' || a[idx] > '9') {
			tmp += a[idx];
		}
		else {
			HNT.push_back(tmp);
			tmp = "";
			break;
		}
	}
	for (int i = 0; i < 5; i++) {
		if (idx == a.size()) {
			break;
		}
		if (a[idx] >= '0' && a[idx] <= '9') {
			tmp += a[idx++];
		}
		else {
			break;
		}
	}
	HNT.push_back(tmp);
	HNT.push_back(a.substr(idx));
	return HNT;
}
bool compare(string a, string b) {
	vector<string> aHNT = processHNT(a);
	vector<string> bHNT = processHNT(b);
	//0¿Ã HEAD, 1¿Ã NUMBER, 2∞° TAIL
	string aHEAD = aHNT[0];
	string bHEAD = bHNT[0];
	transform(aHNT[0].begin(), aHNT[0].end(), aHEAD.begin(), ::toupper);
	transform(bHNT[0].begin(), bHNT[0].end(), bHEAD.begin(), ::toupper);
	if (aHEAD == bHEAD) {
		int aNUMBER = stoi(aHNT[1]);
		int bNUMBER = stoi(bHNT[1]);
		return aNUMBER < bNUMBER;
	}
	return aHEAD < bHEAD;
}
vector<string> solution(vector<string> files) {
	vector<string> answer = files;
	stable_sort(answer.begin(), answer.end(), compare);
	return answer;
}
int main() {
	solution({ "img12.png", "img10.png", "img02.png", "img1.png", "IMG01.GIF", "img2.JPG" });
}