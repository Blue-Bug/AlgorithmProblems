#include <string>
#include <vector>
#include <cstdlib>
#include <unordered_set>
#include <unordered_map>
using namespace std;

vector<int> solution(string s) {
    vector<int> answer;
    unordered_map<int, unordered_set<int>> storage;
    unordered_set<int> nums;
    string tmp = "";
    int cnt = 0;
    for (int i = 2; i < s.size() - 1; i++) {
        if (s[i] == '{' || (s[i] == ',' && s[i - 1] == '}')) {
            continue;
        }
        if (s[i] == ',' && s[i - 1] != '}' || s[i] == '}') {
            nums.insert(atoi(tmp.c_str()));
            tmp = "";
            cnt++;
            if (s[i] == '}') {
                storage[cnt] = nums;
                nums.clear();
                cnt = 0;
            }
        }
        else {
            tmp += s[i];
        }
    }
    for (int i = 1; i <= storage.size(); i++) {
        answer.push_back(*storage[i].begin());
        for (int j = i + 1; j <= storage.size(); j++) {
            storage[j].erase(*storage[i].begin());
        }
    }
    return answer;
}