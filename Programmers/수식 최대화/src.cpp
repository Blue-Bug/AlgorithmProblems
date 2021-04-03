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
		//�켱���� �����ں��� ���ʷ� ã�Ƴ��� ���
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
					//������ �д� ��� üũ
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
					//������ �д°�� üũ
					if (oper == findOper) {
						//ã�� �ִ� �������� ���
						flag = true;
					}
					else {
						//�ƴ� ��� result�� �ִ´�.
						result += to_string(operand1) + oper;
					}
				}
				else {
					//������ ������ �о��� result�� operand1�� �ִ´�.
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