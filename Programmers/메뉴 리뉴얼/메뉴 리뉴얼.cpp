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
        //Check[0]�� A = 1<< 26
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

    //�մԵ��� ��������� ���� ���ĺ��� ��Ʈ�� ��ȯ
    for (auto it : orders) {
        int res = 0;
        for (auto it2 : it) {
            //A�� 65
            //A 1000000... 1 << 26
            //B 0100000... 1 << 25
            int tmp = 1 << (91 - it2);
            res |= tmp;
        }
        bit_orders.push_back(res);
    }

    vector<bit_set>bit_answer(11);
    for (auto it : course) {
        //�ڽ����� ������ ��ǰ�丮�� ������ ����ֵ�
        vector<int> comb_list;
        bool Check[26]{ false };

        combination(comb_list, Check, 0, it);
        //�ڽ��� ���� ��ǰ�޴��� ������ ����� ����

        for (auto it2 : bit_orders) {
            //��Ʈ�� ��ȯ�� ������ ���鼭
            for (auto it3 : comb_list) {
                //������ �� ��ǰ�޴��� ������ ���ԵǾ� �ִٸ� �ڽ� �丮�ĺ���
                if ((it2 & it3) == it3) {
                    auto it4 = bit_answer[it].bit_map.find(it3);

                    if (it4 == bit_answer[it].bit_map.end()) {
                        //���� �ش� �ĺ��� map�� ���ٸ� Ž�� Ƚ�� 1�� ����
                        bit_answer[it].bit_map.insert(make_pair(it3, 1));
                    }
                    else {
                        //���� �ش� �ĺ��� map�� ����ִٸ� Ž�� Ƚ�� ����
                        it4->second += 1;
                    }
                }
            }
        }
    }

    for (auto it : bit_answer) {
        if (it.bit_map.empty()) continue;
        //���� �ڽ� �丮�� ���ٸ� ������

        vector<pair<int, int>> vec(it.bit_map.begin(), it.bit_map.end());
        sort(vec.begin(), vec.end(), compare);
        //map�� ���Ϳ� �ְ� Ž���� Ƚ���� �������� ����

        int max = vec.front().second;
        //�� ���� ���� ū Ž�� Ƚ��

        for (auto it2 : vec) {
            //Ž���� Ƚ���� 2���� ũ�� �ִ��϶��� ���ڷ� ��ȯ
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

    //���ڿ� ����
    sort(answer.begin(), answer.end());
    return answer;
}
int main() {
    vector<string> orders = { "ABCFG", "AC", "CDE", "ACDE", "BCFG", "ACDEH" };
    vector<int> course = { 2,3,4 };
    solution(orders, course);
}