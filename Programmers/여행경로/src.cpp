#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;


vector<string> answer;

bool dfs(string airport,int ticket_num,vector<string> result, unordered_map<string, vector<string>> flights) {
	result.push_back(airport);
	while (!flights[airport].empty()) {
		string next_airport = flights[airport].front();
		flights[airport].erase(flights[airport].begin());
		if (dfs(next_airport, ticket_num, result,flights)) {
			return true;
		}
		else {
			if (flights[airport].empty()) {
				return false;
			}
			flights[airport].push_back(next_airport);
		}
	}
	if (ticket_num != result.size()) {
		//다 돌았는데 남은 표가 있다면
		return false;
	}
	else {
		//정답이면 answer에 넣음
		answer = result;
		return true;
	}
}
	
vector<string> solution(vector<vector<string>> tickets) {
	unordered_map<string, vector<string>> flights;
	for (auto ticket : tickets) {
		flights[ticket.front()].push_back(ticket.back());
	}
	for (auto flight = flights.begin(); flight != flights.end(); flight++) {
		sort(flight->second.begin(), flight->second.end());
		vector<string> tmp;
		vector<string> tmp2;
		for (auto flight_info : flight->second) {
			if (flights.find(flight_info) == flights.end()) {
				tmp.push_back(flight_info);
			}
			else {
				tmp2.push_back(flight_info);
			}
		}
		flight->second = tmp2;
		for (auto pb : tmp) {
			flight->second.push_back(pb);
		}
	}
	int ticket_num = tickets.size()+1;
	vector<string> result;
	dfs("ICN",ticket_num,result,flights);
	return answer;
}