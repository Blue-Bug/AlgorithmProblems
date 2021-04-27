#include <string>
#include <vector>
#include <queue>
using namespace std;

int solution(int bridge_length, int weight, vector<int> truck_weights) {
	int answer = 1;

	queue<pair<int, int>> q;
	int cur_weight = 0;
	int i = 0;
	while (i < truck_weights.size()) {
		if (!q.empty() && answer == q.front().second) {
			cur_weight -= q.front().first;
			q.pop();
		}
		if (cur_weight + truck_weights[i] <= weight) {
			cur_weight += truck_weights[i];
			q.push({ truck_weights[i++], answer + bridge_length });
			answer++;
		}
		else {
			if (!q.empty()) {
				cur_weight -= q.front().first;
				answer = q.front().second;
				q.pop();
			}
		}
	}
	while (!q.empty()) {
		answer = q.front().second;
		q.pop();
	}
	return answer;
}