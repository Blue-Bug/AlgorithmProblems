#include <string>
#include <vector>
#include <algorithm>
using namespace std;


vector<int> solution(int n, int s) {
    vector<int> answer;

    if (s / n == 0) {
        return { -1 };
    }

    while (1) {
        int mmax = s / n--;
        if (s > mmax) {
            answer.push_back(mmax);
            s -= mmax;
        }
        else {
            answer.push_back(s);
            break;
        }
    }

    if (answer.empty()) return { -1 };
    sort(answer.begin(), answer.end());
    return answer;
}