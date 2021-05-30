#include <string>
#include <vector>

using namespace std;

vector<long long> solution(vector<long long> numbers) {
    vector<long long> answer;
    for (auto it : numbers) {
        if (it % 2 == 0) {
            answer.push_back(it + 1);
        }
        else {
            long long lowZero = ~it & (it + 1);
            answer.push_back(it + lowZero - (lowZero >> 1));
        }
    }

    return answer;
}