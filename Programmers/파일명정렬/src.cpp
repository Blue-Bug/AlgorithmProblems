#include <string>
#include <vector>
#include <algorithm>
using namespace std;
vector<string> processHNT(string a) {
	//String에서 Head Number Tail을 뽑아낸다.
	vector<string> HNT;
	string tmp = "";
	int idx = 0;

	//숫자가 아니라면 임시 문자열에 추가하고 숫자가 나오면 멈추고 Head로 저장
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

	//Number는 최대 5개가 연속되므로 5번 루프를 돈다.
	for (int i = 0; i < 5; i++) {
		//문자열의 끝까지 갔거나 숫자가 아니라면 멈추고 Number에 저장
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

	//나머지 남은 문자열은 Tail에 저장
	HNT.push_back(a.substr(idx));
	return HNT;
}
bool compare(string a, string b) {
	vector<string> aHNT = processHNT(a);
	vector<string> bHNT = processHNT(b);
	//0이 HEAD, 1이 NUMBER, 2가 TAIL
	string aHEAD = aHNT[0];
	string bHEAD = bHNT[0];
	transform(aHNT[0].begin(), aHNT[0].end(), aHEAD.begin(), ::toupper);
	transform(bHNT[0].begin(), bHNT[0].end(), bHEAD.begin(), ::toupper);
	//a와 b의 HEAD를 대문자로 변환하고 비교했을때 같다면 NUMBER를 보고 오름차순 정렬
	if (aHEAD == bHEAD) {
		int aNUMBER = stoi(aHNT[1]);
		int bNUMBER = stoi(bHNT[1]);
		return aNUMBER < bNUMBER;
	}
	return aHEAD < bHEAD;
}
vector<string> solution(vector<string> files) {
	vector<string> answer = files;
	//stable sort이므로 모든 조건이 같다면 들어온 순서로 정렬이 된다
	stable_sort(answer.begin(), answer.end(), compare);
	return answer;
}
int main() {
	solution({ "img12.png", "img10.png", "img02.png", "img1.png", "IMG01.GIF", "img2.JPG" });
}