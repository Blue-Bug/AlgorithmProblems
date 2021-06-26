#include <iostream>
#include <string>
#include <regex>
using namespace std;

int main() {
	//잠수함의 패턴 (100~1~|01)~
	string signal;
	cin >> signal;
	
	regex re("(10(0)+(1)+|(01)+)+");
	if (regex_match(signal, re)) {
		cout << "SUBMARINE";
	}
	else {
		cout << "NOISE";
	}
}