#include <string>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;
//처음 생각 -> map<string,queue<int>> kind 하나로 pop해가며 찾기 -> queue 자체도 오름차로 정렬되어있어야됨
//다음 생각 -> 포인터 두개와 set -> last로 한번 훑고 first로 배열 길이를 줄여봄 -> set이라서 first로 지울때 뒤에 보석이 있음에도 지워짐
//앞이나 뒤를 지워도 된다는 것을 알려면 같은 종류의 보석이 어딘가에 하나 더있어야 함을 알아야 한다 -> 처음 생각처럼 인덱스를 적어두거나 카운트해야됨

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
        if (res.size() == kind.size()) {//보석을 전부 골랐으면 first로 돌아가서 해당 보석 개수 감소
            if (res[gems[first]] <= 1) {
                //보석이 없어지게 되면 지움
                res.erase(gems[first++]);
            }
            else {
                res[gems[first++]]--;
            }
        }
        else if (last >= gems.size()) {//배열을 끝까지 봤으면 끝
            break;
        }
        else {
            res[gems[last++]]++; // last 포인터를 증가시키며 해당 보석 개수 증가
        }
        if (res.size() == kind.size()) {//보석을 전부 고른상태에서만 최소 길이를 구함
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