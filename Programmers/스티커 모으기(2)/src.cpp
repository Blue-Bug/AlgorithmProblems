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
    //첫번째를 고르지 않은 경우
    dp[0][0] = 0;
    dp[0][1] = sticker[1];
    //첫번째를 고른 경우
    dp[1][0] = sticker[0];
    dp[1][1] = sticker[0];

    for (int i = 2; i < sticker.size(); i++) {
        //바로 전 값과 2개 전 값에 현재 더한값을 비교후 큰 것을 저장
        dp[0][i] = max(dp[0][i - 1], dp[0][i - 2] + sticker[i]);
        dp[1][i] = max(dp[1][i - 1], dp[1][i - 2] + sticker[i]);
    }
    //첫번째를 고른 경우 마지막 것은 고를 수 없다.
    answer = max(dp[0][size], dp[1][size - 1]);
    return answer;
}