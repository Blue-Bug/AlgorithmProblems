#include <string>
#include <vector>
#include <sstream>
using namespace std;

vector<char> oper = { '+','-','*' };
//expression을 전달받을 변수
string parseString = "";
long long answer = 0;

string strParse(vector<char> mOper) {
	string repeatString = parseString;
	char oper;
	string result = "";

	for (auto findOper : mOper) {
		//우선순위가 빠른 연산자부터 차례로 찾아내서 계산
		long long operand1 = 0;
		long long operand2 = 0;
		bool flag = false;
		stringstream ss;

		//repeatString을 파싱
		ss.str(repeatString);
		while (1) {
			if (flag) {
				//flag가 true면 원하는 연산자를 찾았다는 것
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
				
				//계산 결과를 다시 operand1에 저장한다.
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
					//expression을 끝까지 읽었을 경우 계산한 operand1을 result에 넣는다.
					result += to_string(operand1);
					break;
				}
			}
			else {
				ss >> operand1;
				if (ss >> oper) {
					//끝까지 읽는경우 체크
					if (oper == findOper) {
						//찾고 있던 연산자인 경우에 flag를 true로 만든다.
						flag = true;
					}
					else {
						//아닐 경우 그대로 result에 넣는다.
						result += to_string(operand1) + oper;
					}
				}
				else {
					//끝까지 읽으면 읽었던 operand1을 result에 넣는다.
					result += to_string(operand1);
					break;
				}
				
			}
		}
		ss.clear();
		//중간 결과와 마지막 결과가 repeatString에 다시 저장된다.
		repeatString = result;
		result = "";
	}
	return repeatString;
}

void operBacktrack(vector<int> &check, vector<char> mOper) {
	if (mOper.size() == oper.size()) {
		//모든 연산자가 우선순위 벡터에 들어가게 되면 expression을 계산한다.
		long long result = stoll(strParse(mOper));
		if(abs(result) >= answer){
			answer = abs(result);
		}
		return;
	}
	for (int i = 0; i < oper.size(); i++) {
		//check 벡터를 검사하며 모든 우선순위 경우를 벡터로 만든다.
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

	//check 벡터에는 연산자가 사용됐으면 1 아니면 0을 저장한다.
	vector<int> check(oper.size());
	operBacktrack(check,{});

	return answer;
}