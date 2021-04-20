#include <string>
#include <vector>
#include <cmath>
using namespace std;

string conv_three(int n) {
	string tmp;
	if (n < 3) return to_string(n);
	else {
		tmp = conv_three(n / 3);
		tmp += to_string(n % 3);
		return tmp;
	}
}

int solution(int n) {
	int answer = 0;
	string tmp = conv_three(n);
	for (int i = tmp.size() - 1; i >= 0; i--) {
		answer += (tmp[i] - '0')*pow(3,i);
	}
	return answer;
}