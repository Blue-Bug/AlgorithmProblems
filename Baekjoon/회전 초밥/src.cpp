#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

//접시 수, 가짓수, 연속, 쿠폰
int n, d, k, c;
vector<int> dishes;
//스시 카운팅
int sushi_kind[3001]{ 0 };
int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n >> d >> k >> c;
	int tmp, first = 0, maxSushi = 0,result = 0;

	for (int i = 0; i < n; i++) {
		cin >> tmp;
		dishes.push_back(tmp);
		//해당 스시가 없었다면 결과값 증가
		if (sushi_kind[tmp] == 0) result++;
		sushi_kind[tmp]++;
		if (dishes.size() >= k) {
			if (maxSushi <= result) {
				//같을 경우에 쿠폰을 검사
				if (sushi_kind[c] == 0) {
					maxSushi = result+1;
				}
				else {
					maxSushi = result;
				}
			}
			//맨앞 접시의 스시를 뺀다
			sushi_kind[dishes[first]]--;
			//해당 스시가 없어졌다면 결과값 감소
			if (sushi_kind[dishes[first]] == 0) {
				result--;
			}
			first++;
		}
	}
	int last = 0;

	//last 포인터를 앞으로 옮기고 계속 진행
	while (first != 0) {
		if (sushi_kind[dishes[last]] == 0) result++;
		sushi_kind[dishes[last]]++;
		if (maxSushi <= result) {
			if (sushi_kind[c] == 0) {
				maxSushi = result + 1;
			}
			else {
				maxSushi = result;
			}
		}
		sushi_kind[dishes[first]]--;
		if (sushi_kind[dishes[first]] == 0) {
			result--;
		}
		(++first)%=n;
		(++last)%=n;
	}
	cout << maxSushi;
}