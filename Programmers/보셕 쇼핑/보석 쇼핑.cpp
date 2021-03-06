#include <string>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;
//ó�� ���� -> map<string,queue<int>> kind �ϳ��� pop�ذ��� ã�� -> queue ��ü�� �������� ���ĵǾ��־�ߵ�
//���� ���� -> ������ �ΰ��� set -> last�� �ѹ� �Ȱ� first�� �迭 ���̸� �ٿ��� -> set�̶� first�� ���ﶧ �ڿ� ������ �������� ������
//���̳� �ڸ� ������ �ȴٴ� ���� �˷��� ���� ������ ������ ��򰡿� �ϳ� ���־�� ���� �˾ƾ� �Ѵ� -> ó�� ����ó�� �ε����� ����ΰų� ī��Ʈ�ؾߵ�

set<string> kind;

void setGems(vector<string> gems) {
    for (int i = 0; i < gems.size(); i++) {
        kind.insert(gems[i]);
    }
}

vector<int> solution(vector<string> gems) {
    vector<int> answer;
    answer.push_back(0);
    answer.push_back(0);
    setGems(gems);

    unordered_map<string, int> res;
    int first = 0, last = 0, min_len = 100001;
    while (1) {
        if (res.size() == kind.size()) {//������ ���� ������� first�� ���ư��� �ش� ���� ���� ����
            if (res[gems[first]] <= 1) {
                //������ �������� �Ǹ� ����
                res.erase(gems[first++]);
            }
            else {
                res[gems[first++]]--;
            }
        }
        else if (last >= gems.size()) {//�迭�� ������ ������ ��
            break;
        }
        else {
            res[gems[last++]]++; // last �����͸� ������Ű�� �ش� ���� ���� ����
        }
        if (res.size() == kind.size()) {//������ ���� �����¿����� �ּ� ���̸� ����
            if (min_len > abs(last - first) + 1) {
                min_len = abs(last - first) + 1;
                answer[0] = first + 1;
                answer[1] = last;
            }
        }
    }
    return answer;
}

int main() {
    vector<string> v = { "EAD", "RUB", "EM", "RUB", "EM", "DIA", "EM", "EM", "EM", "RUB", "EAD", "DIA" };
    vector<int> s = solution(v);
    cout << s[0] << ' ' << s[1];
}