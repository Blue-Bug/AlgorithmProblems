#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int solution(int n, vector<int> stations, int w)
{
    int answer = 0;
    int first = 1;
    int end = n;
    int range = (w * 2) + 1;
    for (int i = 0; i <= stations.size(); i++) {
        if (i < stations.size()) {
            end = stations[i] - w - 1;
            if (end < 1) {
                //기지국 위치가 1 이하일때 예외 처리
                first = stations[i] + w + 1;
                continue;
            }
        }
        else if (first <= n) {
            end = n;
        }
        else {
            break;
        }
        float need_Station = (end - first) + 1;
        int tmp = ceil(need_Station / range);

        answer += tmp;

        /*
            int need_Station = (end - first) + 1;
            int tmp = need_Station / range;
            int tmp2 = need_Station % range;

            if(tmp2 != 0) answer += 1;
            if(tmp > 0){
                answer += tmp;
            }
        */
        if (i < stations.size()) {
            first = stations[i] + w + 1;
        }
    }

    return answer;
}