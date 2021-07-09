#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
	string str;
	getline(cin, str);
	string tmp = "";

	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '<') {
			for (int k = tmp.size() - 1; k >= 0; k--) {
				cout << tmp[k];
			}
			cout << str[i];
			for (int k = i + 1; k < str.size(); k++) {
				cout << str[k];
				if (str[k] == '>') {
					i = k;
					break;
				}
			}
			tmp = "";
			continue;
		}
		else if (str[i] == ' ') {
			for (int k = tmp.size() - 1; k >= 0; k--) {
				cout << tmp[k];
			}
			cout << str[i];
			tmp = "";
		}
		else {
			tmp += str[i];
		}
	}
	for (int k = tmp.size() - 1; k >= 0; k--) {
		cout << tmp[k];
	}
}