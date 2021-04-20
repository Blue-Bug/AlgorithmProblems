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
			//�Ʒ��� ������ idx�� ���̸�ŭ ���Ѵ�.
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
			//���������� ������ idx�� 1�� ���Ѵ�.
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
			//���ΰ����� idx�� ���̸�ŭ ����.
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
