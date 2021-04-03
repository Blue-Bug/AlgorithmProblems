#include <string>
#include <vector>
#include <sstream>
using namespace std;

vector<char> oper = { '+','-','*' };
string parseString = "";
long long answer = 0;

string strParse(vector<char> mOper) {
	string repeatString = parseString;
	char oper;
	string result = "";

	for (auto findOper : mOper) {
		//우선순위 연산자부터 차례로 찾아내서 계산
		long long operand1 = 0;
		long long operand2 = 0;
		bool flag = false;
		stringstream ss;
		ss.str(repeatString);
		while (1) {
			if (flag) {
				ss >> operand2;
				if (findOper == '+') {
					operand1 += operand2;
				}
				else if (findOper == '-') {
					operand1 -= operand2;
				}
				else {
					operand1 *= operand2;
				}
				
				flag = false;

				if (ss >> oper) {
					//끝까지 읽는 경우 체크
					if (oper == findOper) {
						flag = true;
					}
					else {
						result += to_string(operand1);
						result += oper;
					}
				}
				else {
					result += to_string(operand1);
					break;
				}
			}
			else {
				ss >> operand1;
				if (ss >> oper) {
					//끝까지 읽는경우 체크
					if (oper == findOper) {
						//찾고 있던 연산자인 경우
						flag = true;
					}
					else {
						//아닐 경우 result에 넣는다.
						result += to_string(operand1) + oper;
					}
				}
				else {
					//끝까지 읽으면 읽었던 result에 operand1을 넣는다.
					result += to_string(operand1);
					break;
				}
				
			}
		}
		ss.clear();
		repeatString = result;
		result = "";
	}
	return repeatString;
}

void operBacktrack(vector<int> &check, vector<char> mOper) {
	if (mOper.size() == oper.size()) {
		long long result = stoll(strParse(mOper));
		if(abs(result) >= answer){
			answer = abs(result);
		}
		return;
	}
	for (int i = 0; i < oper.size(); i++) {
		if (check[i] == 0) {
			mOper.push_back(oper[i]);
			check[i] = 1;
			operBacktrack(check, mOper);
			mOper.pop_back();
			check[i] = 0;
		}
	}
}

long long solution(string expression) {
	parseString = expression;

	//first,second,third
	vector<int> check(oper.size());
	operBacktrack(check,{});

	return answer;
}

int main() {
	solution("100-200*300-500+20");
}