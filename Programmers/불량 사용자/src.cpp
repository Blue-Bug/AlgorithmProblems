#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

bool check[8]{ false };
unordered_set<string> banned;
void find_banned(vector<string>& user_id, vector<string>& banned_id, int idx) {
    if (idx == banned_id.size()) {
        //set으로 중복체크
        string tmp = "";
        for (int i = 0; i < 8; i++) {
            if (check[i]) {
                tmp += user_id[i] + ",";
            }
        }
        tmp = tmp.substr(0, tmp.size() - 1);
        banned.insert(tmp);
        return;
    }
    for (int i = 0; i < user_id.size(); i++) {
        if (check[i] || user_id[i].size() != banned_id[idx].size()) continue;
        //이미 앞에서 고른 아이디라면 넘어감
        for (int j = 0; j <= banned_id[idx].size(); j++) {
            if (j == banned_id[idx].size()) {
                //가능한 아이디라면
                check[i] = true;
                find_banned(user_id, banned_id, idx + 1);
                check[i] = false;
            }
            else if (user_id[i][j] != banned_id[idx][j] && banned_id[idx][j] != '*') {
                //길이만 같고 다른 아이디라면
                break;
            }
        }
    }
    return;
}


int solution(vector<string> user_id, vector<string> banned_id) {
    find_banned(user_id, banned_id, 0);
    return banned.size();
}