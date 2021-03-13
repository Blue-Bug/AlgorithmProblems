#include <iostream>
#include <cmath>
using namespace std;

int solution(int n, int a, int b)
{
	//answer는 a와 b가 만날때까지 걸리는 횟수
	int answer = 1;
	while (1) {
		//a와 b의 차가 1이고 
		if (abs(a - b) ==1) {
			//a가 짝수일때 b가 a보다 1이 작거나 || a가 홀수일때 b가 a보다 1이 크다면 둘이 만나게 된 것
			if ((a % 2 == 0 && a - 1 == b) || (a % 2 == 1 && a + 1 == b)) {
				return answer;
			}
		}
		//a가 짝수라면 다음 대전에서는 a/2의 번호를 가지게 됨
		if (a % 2 == 0) {
			a /= 2;
		}
		//a가 홀수라면 다음 대전에서는 a+1/2의 번호를 가지게 됨
		else {
			a = (a+1)/2;
		}
		//b도 a와 같다
		if (b % 2 == 0) {
			b /= 2;
		}
		else {
			b = (b + 1) / 2;
		}
		answer++;
	}
}