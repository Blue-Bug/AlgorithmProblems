#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

int solution(int m, int n, vector<string> board) {
	int answer = 0;
	bool flag = true;

	//board�� �ִ� ������ �״�� copy���Ϳ� �����ؿ´�.
	vector<vector<char>> copy(n);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			copy[i].push_back(board[i][j]);
		}
	}

	//�������� �͵��� ���������� �ݺ��Ѵ�.
	while (flag) {
		//i��° �࿡ ���° ���� ���������� ������ unordered_map
		unordered_map<int, unordered_set<int>> mm;
		flag = false;

		//2x2�� ���鼭 �ϴ� �����
		for (int i = 0; i < m - 1; i++) {
			for (int j = 0; j < n - 1; j++) {
				//copy���� �ϳ��� �����ͼ�
				char str = copy[i][j];
				//�� ���� x��� ����ִٴ� �ǹ��̹Ƿ� �Ѿ��
				if (str == 'x') { continue; }
				//������ �پ��ִ� 3���� ���� ���� ���ٸ� �� ������ mm�� �߰��Ѵ�.
				if (copy[i][j + 1] == str && copy[i + 1][j] == str && copy[i + 1][j + 1] == str) {
					mm[i].insert(j + 1);
					mm[i].insert(j);
					mm[i + 1].insert(j);
					mm[i + 1].insert(j + 1);

					//������ �͵��� �����Ƿ� flag�� true�� �ٲ۴�.
					flag = true;
				}
			}
		}

		//copy2 ���Ϳ��� copy���� ������ ������ ���� ��ϵ��� �Ʒ��� �������� �����Ѵ�.
		vector<vector<char>> copy2(n);
		//�� �Ʒ� ����� �ö󰡸� üũ�� ��
		int idx = m - 1;

		//��� ������, ù��° ���� �ǾƷ� ����� �� ������� üũ�ϸ� ���� ���� �Ѿ��.
		for (int j = 0; j < n; j++) {
			for (int i = m - 1; i >= 0; i--) {
				//������ mm�� �࿡ �����ߴ� set�� �ش� ���� �ִ��� Ȯ���Ѵ�.
				if (mm[i].find(j) == mm[i].end()) {
					//�������� �ʾҴٸ� copy2�� �߰�
					copy2[idx--].push_back(copy[i][j]);
				}
			}
			for (int k = idx; k >= 0; k--) {
				//�������� ������ ���̹Ƿ� ����ִ� ��鿡 x�� �߰��Ѵ�.
				copy2[k].push_back('x');
			}
			idx = m - 1;
		}
		//copy2�� copy�� �����ϰ� ������ ��ŭ mm�� ũ�⸦ answer�� �߰��Ѵ�.
		copy = copy2;
		for (auto tmp : mm) {
			answer += tmp.second.size();
		}
	}
	
	return answer;
}