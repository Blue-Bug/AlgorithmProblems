#include <iostream>
#include <cmath>
using namespace std;

int solution(int n, int a, int b)
{
	//answer�� a�� b�� ���������� �ɸ��� Ƚ��
	int answer = 1;
	while (1) {
		//a�� b�� ���� 1�̰� 
		if (abs(a - b) ==1) {
			//a�� ¦���϶� b�� a���� 1�� �۰ų� || a�� Ȧ���϶� b�� a���� 1�� ũ�ٸ� ���� ������ �� ��
			if ((a % 2 == 0 && a - 1 == b) || (a % 2 == 1 && a + 1 == b)) {
				return answer;
			}
		}
		//a�� ¦����� ���� ���������� a/2�� ��ȣ�� ������ ��
		if (a % 2 == 0) {
			a /= 2;
		}
		//a�� Ȧ����� ���� ���������� a+1/2�� ��ȣ�� ������ ��
		else {
			a = (a+1)/2;
		}
		//b�� a�� ����
		if (b % 2 == 0) {
			b /= 2;
		}
		else {
			b = (b + 1) / 2;
		}
		answer++;
	}
}