#include <iostream>
#include <cmath>
using namespace std;

int solution(int n, int a, int b)
{
	int answer = 1;
	while (1) {
		if (abs(a - b) ==1) {
			if ((a % 2 == 0 && a - 1 == b) || (a % 2 == 1 && a + 1 == b)) {
				return answer;
			}
		}
		if (a % 2 == 0) {
			a /= 2;
		}
		else {
			a += 1;
			a /= 2;
		}
		if (b % 2 == 0) {
			b /= 2;
		}
		else {
			b += 1;
			b /= 2;
		}
		answer++;
	}
}