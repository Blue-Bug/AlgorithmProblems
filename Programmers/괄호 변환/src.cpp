#include <string>
#include <vector>
#include <stack>
using namespace std;

string stageOnetoThree(string p) {
	if (p.size() > 0) {
		string u = "";
		string v = "";

		int l = 0;
		int r = 0;
		//올바른 괄호 문자열을 먼저 뽑아낸다.
		for (int i = 0; i < p.size(); i++) {
			if (l == r && l != 0) {
				v = p.substr(i);
				break;
			}
			if (p[i] == '(') {
				l++;
			}
			else {
				r++;
			}
			u += p[i];
		}
		stack<char> s;
		bool isRight = false;
		for (auto i : u) {
			if (i == '(') {
				s.push(i);
			}
			else if (!s.empty() && i == ')') {
				s.pop();
			}
			else {
				isRight = true;
				break;
			}
		}
		if (isRight) {
			string tmp = "(";
			tmp += stageOnetoThree(v) + ")";
			string new_u = "";
			//뒤집기
			for (int i = 1; i < u.size() - 1; i++) {
				if (u[i] == '(') {
					new_u += ")";
				}
				else {
					new_u += "(";
				}
			}
			tmp += new_u;
			return tmp;
		}
		else {
			u += stageOnetoThree(v);
			return u;
		}
	}
	else {
		return "";
	}
}

string solution(string p) {
	string answer = "";
	answer = stageOnetoThree(p);

	return answer;
}