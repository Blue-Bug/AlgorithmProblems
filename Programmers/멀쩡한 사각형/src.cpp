#include <cmath>
#define ld  long double
using namespace std;

long long solution(int w, int h) {
	long long answer = 0;
	//����*x�� = ��ȭ��
	long long res = 0;
	for (int i = 1; i < w; i++) {
		//�Ҽ������� ���� ���� ���� -> ��������
		res = (ld)h *(ld)i / (ld)w;
		answer += res;
	}
	//������ ���̸� ���߱⶧���� 2�� �����ش�.
	answer *= 2;

	return answer;
}