#include <string>
#include <vector>

using namespace std;

int solution(string skill, vector<string> skill_trees) {
	int answer = 0;
	//��ųƮ���� ���� ��ų�� ���µ� ���� ���� ��ų�� �ִٸ�
	//��������� Ȯ��, �ȹ�m���� �������� �Ѿ
	for (auto it : skill_trees) {
		bool can_Learn = true;
		bool learned[27]{ false };
		for (int j = 0; j < it.size(); j++) {
			//��� �� ���� ��ų�̶�� üũ�Ǹ� �� ��ųƮ���� ����
			if (!can_Learn) break;

			//���ེų�� ���� ��ųƮ���� ��� ��ų�� ���Ѵ�
			for (int i = 0; i < skill.size(); i++) {
				//���� ���� ��ųƮ������ �����ִ� ��ų�� ���ེų�ȿ� �ִٸ�
				if (it[j] == skill[i]) {
					bool check_Condition = true;
					//���� ��ų�� ������� Ȯ���Ѵ� -> ���ེų ���������� �ε����� ������ üũ�迭�� Ȯ��
					for (int k = 0; k < i; k++) {
						//�ȹ������ ���� ���� ��ųƮ����
						if (learned[k] == false) {
							check_Condition = false;
							break;
						}
					}
					if (check_Condition) {
						//���� ��ų�� �����ϸ� �� ��ų�� ����ٰ� ǥ���� �� �ִ�
						learned[i] = true;
						break;
					}
					else {
						//���� ��ų�� �������� ������ ��� �� ���� ��ųƮ���̹Ƿ� ��� �� ���ٰ� ǥ��
						can_Learn = false;
						break;
					}
				}
			}
		}
		//��� �� ������ �� ���� ����
		if (can_Learn) answer += 1;
	}
	return answer;
}