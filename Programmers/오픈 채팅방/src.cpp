#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

vector<string> solution(vector<string> record) {
    vector<string> answer;
    vector<vector<string>> record_frag;
    unordered_map <string, string> users;
    for (auto it : record) {
        string tmp = "";
        vector<string> frag;
        for (int i = 0; i < it.size(); i++) {
            if (i == it.size() - 1) {
                tmp += it[i];
                frag.push_back(tmp);
            }
            else if (it[i] == ' ') {
                frag.push_back(tmp);
                tmp = "";
            }
            else {
                tmp += it[i];
            }
        }
        record_frag.push_back(frag);
    }
    for (auto it : record_frag) {
        if (it[0] == "Enter" || it[0] == "Change") {
            users[it[1]] = it[2];
        }
    }
    for (auto it : record_frag) {
        if (it[0] == "Enter") {
            answer.push_back(users.at(it[1]) + "´ÔÀÌ µé¾î¿Ô½À´Ï´Ù.");
        }
        else if (it[0] == "Leave") {
            answer.push_back(users.at(it[1]) + "´ÔÀÌ ³ª°¬½À´Ï´Ù.");
        }
    }
    return answer;
}

int main() {
    vector<string> record = { "Enter uid1234 Muzi", "Enter uid4567 Prodo","Leave uid1234",
        "Enter uid1234 Prodo","Change uid4567 Ryan" };
    solution(record);
}