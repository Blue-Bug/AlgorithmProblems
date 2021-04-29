#include <string>
#include <vector>
using namespace std;

vector<int> answer;

void find_referral(vector<string>& enroll, vector<string>& referral, int idx, int sendMoney) {
    if (sendMoney <= 0) {
        return;
    }
    if (referral[idx] == "-") {
        answer[idx] -= sendMoney;
        return;
    }
    answer[idx] -= sendMoney;
    for (int i = 0; i < idx; i++) {
        if (enroll[i] == referral[idx]) {
            answer[i] += sendMoney;
            find_referral(enroll, referral, i, sendMoney / 10);
            return;
        }
    }
}

vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount) {
    answer = vector<int>(enroll.size(), 0);

    for (int i = 0; i < seller.size(); i++) {
        int earnedMoney = amount[i] * 100;
        int sendMoney = earnedMoney / 10;
        //추천인을 찾는다.
        for (int j = 0; j < enroll.size(); j++) {
            //명부에서 판매원의 이름을 찾는다.
            if (enroll[j] == seller[i] && !check[j]) {
                answer[j] += earnedMoney;
                if (sendMoney <= 0) {
                    break;
                }
                //===== 동명이인이 아니라 그냥 같은 사람이 두번 나온것이었음=====
                //같은 이름이 있을수도 있으므로 해당 이름의 판매원을
                //처리했음을 체크해둔다.
                //check[j] = true;

                //referral 배열에는 판매원을 참여시킨 사람의 이름이 있다.
                //참여시킨 사람의 이름은 판매원보다 위에 있음이 보장된다.
                //자신의 추천인을 따라 올라가며 루트까지 수익을 분해하는 것을 반복한다.
                find_referral(enroll, referral, j, sendMoney);
            }
        }
    }
    return answer;
}