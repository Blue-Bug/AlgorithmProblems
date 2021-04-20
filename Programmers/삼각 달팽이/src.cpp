#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

vector<int> solution(int n) {
	int end = (n * (n + 1))/2;
	string control = "down";
	vector<int> answer(end);
	int idx = 0;
	int curheight = 1;
	int maxcnt = n;
	int val = 1;
	int curcnt = 1;
	while (val <= end) {
		answer[idx] = val++;
		if (control == "down") {
			//아래로 갈때는 idx에 높이만큼 더한다.
			if (curcnt == maxcnt) {
				control = "right";
				curcnt = 1;
				idx += 1;
				maxcnt--;
			}
			else {
				idx += curheight++;
				curcnt++;
			}
		}
		else if (control == "right") {
			//오른쪽으로 갈때는 idx에 1씩 더한다.
			if (curcnt == maxcnt) {
				control = "up";
				curcnt = 1;
				idx -= curheight--;
				maxcnt--;
			}
			else {
				idx += 1;
				curcnt++;
			}
			
		}
		else if (control == "up") {
			//위로갈때는 idx에 높이만큼 뺀다.
			if (curcnt == maxcnt) {
				control = "down";
				idx += curheight++;
				curcnt = 1;
				maxcnt--;
			}
			else {
				idx -= curheight--;
				curcnt++;
			}
		}
	}
	return answer;
}
