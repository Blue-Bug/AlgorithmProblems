#include <string>
#include <vector>
#include <sstream>
using namespace std;

vector<char> oper = { '+','-','*' };
//expression�� ���޹��� ����
string parseString = "";
long long answer = 0;

string strParse(vector<char> mOper) {
	string repeatString = parseString;
	char oper;
	string result = "";

	for (auto findOper : mOper) {
		//�켱������ ���� �����ں��� ���ʷ� ã�Ƴ��� ���
		long long operand1 = 0;
		long long operand2 = 0;
		bool flag = false;
		stringstream ss;

		//repeatString�� �Ľ�
		ss.str(repeatString);
		while (1) {
			if (flag) {
				//flag�� true�� ���ϴ� �����ڸ� ã�Ҵٴ� ��
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
				
				//��� ����� �ٽ� operand1�� �����Ѵ�.
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
					//expression�� ������ �о��� ��� ����� operand1�� result�� �ִ´�.
					result += to_string(operand1);
					break;
				}
			}
			else {
				ss >> operand1;
				if (ss >> oper) {
					//������ �д°�� üũ
					if (oper == findOper) {
						//ã�� �ִ� �������� ��쿡 flag�� true�� �����.
						flag = true;
					}
					else {
						//�ƴ� ��� �״�� result�� �ִ´�.
						result += to_string(operand1) + oper;
					}
				}
				else {
					//������ ������ �о��� operand1�� result�� �ִ´�.
					result += to_string(operand1);
					break;
				}
				
			}
		}
		ss.clear();
		//�߰� ����� ������ ����� repeatString�� �ٽ� ����ȴ�.
		repeatString = result;
		result = "";
	}
	return repeatString;
}

void operBacktrack(vector<int> &check, vector<char> mOper) {
	if (mOper.size() == oper.size()) {
		//��� �����ڰ� �켱���� ���Ϳ� ���� �Ǹ� expression�� ����Ѵ�.
		long long result = stoll(strParse(mOper));
		if(abs(result) >= answer){
			answer = abs(result);
		}
		return;
	}
	for (int i = 0; i < oper.size(); i++) {
		//check ���͸� �˻��ϸ� ��� �켱���� ��츦 ���ͷ� �����.
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

	//check ���Ϳ��� �����ڰ� �������� 1 �ƴϸ� 0�� �����Ѵ�.
	vector<int> check(oper.size());
	operBacktrack(check,{});

	return answer;
}