#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<int> sticker)
{
    int answer = 0;
    int dp[2][100000];
    int size = sticker.size() - 1;
    if (size == 0) {
        return sticker.front();
    }
    //ù��°�� ���� ���� ���
    dp[0][0] = 0;
    dp[0][1] = sticker[1];
    //ù��°�� �� ���
    dp[1][0] = sticker[0];
    dp[1][1] = sticker[0];

    for (int i = 2; i < sticker.size(); i++) {
        //�ٷ� �� ���� 2�� �� ���� ���� ���Ѱ��� ���� ū ���� ����
        dp[0][i] = max(dp[0][i - 1], dp[0][i - 2] + sticker[i]);
        dp[1][i] = max(dp[1][i - 1], dp[1][i - 2] + sticker[i]);
    }
    //ù��°�� �� ��� ������ ���� �� �� ����.
    answer = max(dp[0][size], dp[1][size - 1]);
    return answer;
}