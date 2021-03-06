#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <regex>

using namespace std;

string solution(string new_id) {
    string answer = "";
    transform(new_id.begin(), new_id.end(), new_id.begin(), ::tolower);

    //2�ܰ�
    new_id = regex_replace(new_id, regex("\[^(0-9a-z-_.)]"), "");
    new_id = regex_replace(new_id, regex("\[\(\)]"), "");

    //3�ܰ�
    new_id = regex_replace(new_id, regex("\\.{2,}"), ".");

    //4�ܰ�
    if (new_id[0] == '.') {
        new_id = new_id.substr(1);
    }
    if (new_id[new_id.size() - 1] == '.') {
        new_id.resize(new_id.size() - 1);
    }

    //5�ܰ�
    if (new_id.size() == 0) {
        new_id = "a";
    }

    //6�ܰ�
    if (new_id.size() >= 16) {
        new_id.resize(15);
        if (new_id[new_id.size() - 1] == '.') {
            new_id.resize(14);
        }
    }

    //7�ܰ�
    if (new_id.size() <= 2) {
        char tmp = new_id.back();
        for (int i = new_id.size(); i < 3; i++) {
            new_id += tmp;
        }
    }

    //��
    answer = new_id;
    return answer;
}

int main() {
    string t;
    cin >> t;
    cout << solution(t);
}