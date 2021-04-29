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
        //��õ���� ã�´�.
        for (int j = 0; j < enroll.size(); j++) {
            //��ο��� �Ǹſ��� �̸��� ã�´�.
            if (enroll[j] == seller[i] && !check[j]) {
                answer[j] += earnedMoney;
                if (sendMoney <= 0) {
                    break;
                }
                //===== ���������� �ƴ϶� �׳� ���� ����� �ι� ���°��̾���=====
                //���� �̸��� �������� �����Ƿ� �ش� �̸��� �Ǹſ���
                //ó�������� üũ�صд�.
                //check[j] = true;

                //referral �迭���� �Ǹſ��� ������Ų ����� �̸��� �ִ�.
                //������Ų ����� �̸��� �Ǹſ����� ���� ������ ����ȴ�.
                //�ڽ��� ��õ���� ���� �ö󰡸� ��Ʈ���� ������ �����ϴ� ���� �ݺ��Ѵ�.
                find_referral(enroll, referral, j, sendMoney);
            }
        }
    }
    return answer;
}