#include <string>
#include <vector>
#include <set>
using namespace std;

vector<int> solution(vector<int> numbers) {
	vector<int> answer;
	set <int> nset;
	for (int i = 0; i < numbers.size(); i++) {
		for (int j = 0; j < numbers.size(); j++) {
			if (i == j) continue;
			nset.insert(numbers[i] + numbers[j]);
		}
	}
	for (auto num : nset) {
		answer.push_back(num);
	}
	return answer;
}