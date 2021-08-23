#include <iostream>
#include <list>
#include <string>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n;
	cin >> n;
	while (n--) {
		string str;
		cin >> str;
		list<char> password;
		list<char>::iterator iter = password.begin();
		for (int i = 0; i < str.size(); i++) {
			if (str[i] == '<') {
				if (iter != password.begin()) {
					iter--;
				}
			}
			else if (str[i] == '>') {
				if (iter != password.end()) {
					iter++;
				}
			}
			else if (str[i] == '-') {
				if (iter != password.begin()) {					
					iter--;
					iter = password.erase(iter);
				}
			}
			else {
				password.insert(iter, str[i]);			
			}
		}
		for (auto it : password) {
			cout << it;
		}
		cout << '\n';
	}
}