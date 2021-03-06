#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

int solution(vector<vector<string>> clothes) {
    int answer = 0;
    answer = 1;
    unordered_map <string, vector<string>> clothes_map;
    for (auto it : clothes) {
        clothes_map[it[1]].push_back(it[0]);
    }
    // 종류별 개수(입는 경우)+ 안입는 경우
    for (auto it : clothes_map) {
        answer *= it.second.size() + 1;
    }
    //전부 안입는 경우를 빼준다
    return answer - 1;
}

int main() {
    vector<vector<string>> clothes = {
        { "yellowhat", "headgear" },
        { "bluesunglasses", "eyewear" },
        { "green_turban", "headgear" }
    };
    solution(clothes);
}