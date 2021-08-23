#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

//���� ��, ������, ����, ����
int n, d, k, c;
vector<int> dishes;
//���� ī����
int sushi_kind[3001]{ 0 };
int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n >> d >> k >> c;
	int tmp, first = 0, maxSushi = 0,result = 0;

	for (int i = 0; i < n; i++) {
		cin >> tmp;
		dishes.push_back(tmp);
		//�ش� ���ð� �����ٸ� ����� ����
		if (sushi_kind[tmp] == 0) result++;
		sushi_kind[tmp]++;
		if (dishes.size() >= k) {
			if (maxSushi <= result) {
				//���� ��쿡 ������ �˻�
				if (sushi_kind[c] == 0) {
					maxSushi = result+1;
				}
				else {
					maxSushi = result;
				}
			}
			//�Ǿ� ������ ���ø� ����
			sushi_kind[dishes[first]]--;
			//�ش� ���ð� �������ٸ� ����� ����
			if (sushi_kind[dishes[first]] == 0) {
				result--;
			}
			first++;
		}
	}
	int last = 0;

	//last �����͸� ������ �ű�� ��� ����
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