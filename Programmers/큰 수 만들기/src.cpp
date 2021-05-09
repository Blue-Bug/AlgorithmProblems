#include <string>
#include <vector>

using namespace std;

string solution(string number, int k) {
    string answer = "";
    int n = number.size();
    k = n - k;
    char MAX = '0';
    int idx = -1;
    while (k > 0) {
        if (idx + 1 + k == n) {
            for (int i = idx + 1; i < n; i++) {
                answer += number[i];
            }
            return answer;
        }
        else {
            for (int i = idx + 1; i <= n - k; i++) {
                if (number[i] > MAX) {
                    MAX = number[i];
                    idx = i;
                }
            }
            answer += MAX;
        }
        MAX = '0';
        k--;
    }

    return answer;
}