#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct bit_set {
    unordered_map<int, int> bit_map;
};

bool compare(pair<int, int>& a, pair<int, int>& b) {
    return a.second > b.second;
}

void combination(vector<int>& comb_list, bool Check[], int start, int r) {
    if (r == 0) {
        int tmp = 0;
        //Check[0]은 A = 1<< 26
        //ABC 
        for (int i = 0; i < 26; i++) {
            if (Check[i] == true) {
                tmp |= 1 << (26 - i);
            }
        }
        comb_list.push_back(tmp);
    }
    else {
        for (int i = start; i < 26; i++) {
            if (Check[i] == true) continue;
            Check[i] = true;
            combination(comb_list, Check, i, r - 1);
            Check[i] = false;
        }
    }
}

vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> answer;
    vector<int>bit_orders;

    //손님들의 오더목록을 보고 알파벳을 비트로 변환
    for (auto it : orders) {
        int res = 0;
        for (auto it2 : it) {
            //A가 65
            //A 1000000... 1 << 26
            //B 0100000... 1 << 25
            int tmp = 1 << (91 - it2);
            res |= tmp;
        }
        bit_orders.push_back(res);
    }

    vector<bit_set>bit_answer(11);
    for (auto it : course) {
        //코스에는 조합할 단품요리의 개수가 들어있따
        vector<int> comb_list;
        bool Check[26]{ false };

        combination(comb_list, Check, 0, it);
        //코스에 따라 단품메뉴의 조합을 만들어 낸다

        for (auto it2 : bit_orders) {
            //비트로 전환한 오더를 돌면서
            for (auto it3 : comb_list) {
                //조합해 온 단품메뉴가 오더에 포함되어 있다면 코스 요리후보임
                if ((it2 & it3) == it3) {
                    auto it4 = bit_answer[it].bit_map.find(it3);

                    if (it4 == bit_answer[it].bit_map.end()) {
                        //만약 해당 후보가 map에 없다면 탐지 횟수 1로 삽입
                        bit_answer[it].bit_map.insert(make_pair(it3, 1));
                    }
                    else {
                        //만약 해당 후보가 map에 들어있다면 탐지 횟수 증가
                        it4->second += 1;
                    }
                }
            }
        }
    }

    for (auto it : bit_answer) {
        if (it.bit_map.empty()) continue;
        //만들어낸 코스 요리가 없다면 지나감

        vector<pair<int, int>> vec(it.bit_map.begin(), it.bit_map.end());
        sort(vec.begin(), vec.end(), compare);
        //map을 벡터에 넣고 탐지된 횟수를 내림차순 정렬

        int max = vec.front().second;
        //맨 앞이 제일 큰 탐지 횟수

        for (auto it2 : vec) {
            //탐지된 횟수가 2보다 크고 최대일때만 문자로 변환
            if (it2.second == max && max >= 2) {
                string res;
                //A = 1 << 26 -> 91 - 26 = 65 
                for (int i = 26; i >= 1; i--) {
                    int t = 1 << i;
                    if ((it2.first & t) == t) {
                        char tmp = (91 - i);
                        res += tmp;
                    }
                }
                answer.push_back(res);
            }
        }
    }

    //문자열 정렬
    sort(answer.begin(), answer.end());
    return answer;
}
int main() {
    vector<string> orders = { "ABCFG", "AC", "CDE", "ACDE", "BCFG", "ACDEH" };
    vector<int> course = { 2,3,4 };
    solution(orders, course);
}