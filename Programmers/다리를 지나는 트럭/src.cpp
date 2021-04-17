#include <string>
#include <vector>
#include <queue>
using namespace std;

int solution(int bridge_length, int weight, vector<int> truck_weights) {
	int answer = 0;

	queue<pair<int,int>> q;
	int cur_weight = 0;
	for (int i = 0; i < truck_weights.size();) {
		if (cur_weight + truck_weights[i] <= weight) {
			cur_weight += truck_weights[i];
			q.push({ truck_weights[i++],answer + bridge_length });
		}
		if(answer == q.front().second){
			cur_weight -= q.front().first;
			q.pop();
		}
		answer++;
	}

	if (!q.empty()) {
		answer += q.front().second;
	}
	return answer;
}

int main() {
	solution(100, 100, { 10,10,10,10,10,10,10,10,10,10 });
}