#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

//로마 문자의 정수 값이 저장될 맵
unordered_map<string, int> rome_value;

//I,X,C,M이 연속으로 3번 쓰였는지 확인하는 플래그 벡터
vector<int> IXCMFlag(4, 0);

//로마 문자를 정수로 변환하는 함수
int getRomeValue(string rome1) {
	int rome1_value = 0;
	string tmp = "";

	for (int i = 0; i < rome1.size(); i++) {
		//유의해야 하는 경우의 조건을 보면서 리턴 값을 증가
		if (i < rome1.size() - 1) {
			if (rome1[i] == 'I') {
				if (rome1[i + 1] == 'V') {
					rome1_value += 4;
					i += 1;
					continue;
				}
				else if (rome1[i + 1] == 'X') {
					rome1_value += 9;
					i += 1;
					continue;
				}
			}
			else if (rome1[i] == 'X') {
				if (rome1[i + 1] == 'L') {
					rome1_value += 40;
					i += 1;
					continue;
				}
				else if (rome1[i + 1] == 'C') {
					rome1_value += 90;
					i += 1;
					continue;
				}
			}
			else if (rome1[i] == 'C') {
				if (rome1[i + 1] == 'D') {
					rome1_value += 400;
					i += 1;
					continue;
				}
				else if (rome1[i + 1] == 'M') {
					rome1_value += 900;
					i += 1;
					continue;
				}
			}
		}
		tmp = rome1[i];
		rome1_value += rome_value[tmp];
	}
	return rome1_value;
}

//I,X,C,M 플래그를 초기화 해주는 함수
void initIXCMFlag(int except){
	for (int i =0; i<4; i++){
		if (except == i) {
			continue;
		}
		IXCMFlag[i] = 0;
	}
}
vector<string> solution(string rome1,string rome2) {
	vector<string> answer;
	//rome_value 맵에 각 로마 문자 값을 넣어준다.
	rome_value["I"] = 1;
	rome_value["V"] = 5;
	rome_value["X"] = 10;
	rome_value["L"] = 50;
	rome_value["C"] = 100;
	rome_value["D"] = 500;
	rome_value["M"] = 1000;
	rome_value["CM"] = 900;
	rome_value["CD"] = 400;
	rome_value["XC"] = 90;
	rome_value["XL"] = 40;
	rome_value["IX"] = 9;
	rome_value["IV"] = 4;

	//전달 받은 rome1,rome2 문자를 정수로 변환하고 더해준다.
	int rome1_value = getRomeValue(rome1);
	int rome2_value = getRomeValue(rome2);
	int rome_sum = rome1_value + rome2_value;

	answer.push_back(to_string(rome_sum));
	
	string rome_sum_str = "";
	string tmp;
	//한번만 쓸수 있는 문자들의 플래그
	bool V_FLAG = false;
	bool L_FLAG = false;
	bool D_FLAG = false;
	bool CM_FLAG = false;
	bool CD_FLAG = false;
	bool XC_FLAG = false;
	bool XL_FLAG = false;
	bool IV_FLAG = false;
	bool IX_FLAG = false;
	while (rome_sum > 0) {
		//위에서 구한 rome_sum의 값을 0이 될때까지 줄여가며 조건 체크
		if (rome_sum >= 1000 && IXCMFlag[3] < 3) {
			tmp = 'M';
			IXCMFlag[3]++;
			initIXCMFlag(3);
		}
		else if (rome_sum >= 900 && !CM_FLAG && !CD_FLAG) {
			tmp = "CM";
			CM_FLAG = true;
			initIXCMFlag(-1);
		}
		else if (rome_sum >= 500 && !D_FLAG) {
			tmp = "D";
			D_FLAG = true;
			initIXCMFlag(-1);
		}
		else if (rome_sum >= 400 && !CD_FLAG && !CM_FLAG) {
			tmp = "CD";
			CD_FLAG = true;
			initIXCMFlag(-1);
		}
		else if (rome_sum >= 100 && IXCMFlag[2] < 3) {
			tmp = "C";
			IXCMFlag[2]++;
			initIXCMFlag(2);
		}
		else if (rome_sum >= 90 && !XC_FLAG && !XL_FLAG) {
			tmp = "XC";
			XC_FLAG = true;
			initIXCMFlag(-1);
		}
		else if(rome_sum >= 50 && !L_FLAG){
			tmp = "L";
			L_FLAG = true;
			initIXCMFlag(-1);
		}
		else if (rome_sum >= 40 && !XL_FLAG && !XC_FLAG) {
			tmp = "XL";
			XL_FLAG = true;
			initIXCMFlag(-1);
		}
		else if (rome_sum >= 10&& IXCMFlag[1] < 3) {
			tmp = "X";
			IXCMFlag[1]++;
			initIXCMFlag(1);
		}
		else if (rome_sum >= 9 && !IX_FLAG && !IV_FLAG) {
			tmp = "IX";
			IX_FLAG = true;
			initIXCMFlag(-1);
		}
		else if (rome_sum >= 5 && !V_FLAG) {
			tmp = "V";
			V_FLAG = true;
			initIXCMFlag(-1);
		}
		else if (rome_sum >= 4 && !IV_FLAG && !IX_FLAG) {
			tmp = "IV";
			IV_FLAG = true;
			initIXCMFlag(-1);
		}
		else {
			tmp = "I";
			IXCMFlag[0]++;
			initIXCMFlag(0);
		}
		rome_sum -= rome_value[tmp];
		rome_sum_str += tmp;
	}
	answer.push_back(rome_sum_str);
	return answer;
}

int main() {
	string rome1;
	string rome2;
	cin >> rome1 >> rome2;
	vector<string> answer = solution(rome1,rome2);
	for (auto str : answer) {
		cout << str << endl;
	}
}