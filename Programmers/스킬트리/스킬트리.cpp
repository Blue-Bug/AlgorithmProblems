#include <string>
#include <vector>

using namespace std;

int solution(string skill, vector<string> skill_trees) {
	int answer = 0;
	//스킬트리를 보고 스킬을 보는데 만약 선행 스킬이 있다면
	//배웠는지를 확인, 안배웟으면 다음꺼로 넘어감
	for (auto it : skill_trees) {
		bool can_Learn = true;
		bool learned[27]{ false };
		for (int j = 0; j < it.size(); j++) {
			//배울 수 없는 스킬이라고 체크되면 이 스킬트리를 버림
			if (!can_Learn) break;

			//선행스킬과 현재 스킬트리의 모든 스킬을 비교한다
			for (int i = 0; i < skill.size(); i++) {
				//만약 현재 스킬트리에서 보고있는 스킬이 선행스킬안에 있다면
				if (it[j] == skill[i]) {
					bool check_Condition = true;
					//선행 스킬을 배웠는지 확인한다 -> 선행스킬 이전까지의 인덱스를 가지고 체크배열을 확인
					for (int k = 0; k < i; k++) {
						//안배웠으면 배울수 없는 스킬트리임
						if (learned[k] == false) {
							check_Condition = false;
							break;
						}
					}
					if (check_Condition) {
						//선행 스킬을 만족하면 이 스킬을 배웠다고 표시할 수 있다
						learned[i] = true;
						break;
					}
					else {
						//선행 스킬이 만족되지 않으면 배울 수 없는 스킬트리이므로 배울 수 없다고 표시
						can_Learn = false;
						break;
					}
				}
			}
		}
		//배울 수 있으면 답 갯수 증가
		if (can_Learn) answer += 1;
	}
	return answer;
}