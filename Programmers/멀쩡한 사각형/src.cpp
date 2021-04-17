#include <cmath>
#define ld  long double
using namespace std;

long long solution(int w, int h) {
	long long answer = 0;
	//기울기*x값 = 변화량
	long long res = 0;
	for (int i = 1; i < w; i++) {
		//소수점으로 인한 연산 오류 -> 순서변경
		res = (ld)h *(ld)i / (ld)w;
		answer += res;
	}
	//반절의 넓이를 구했기때문에 2를 곱해준다.
	answer *= 2;

	return answer;
}