#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

struct Edge {
    int target_node;
    int weight;
    Edge(int t, int w) { target_node = t; weight = w; }
};
//Edge 구조체 -> 이어진 노드와 가중치 정보가 담겨있다.

class UndirectedGraph {
public:
    UndirectedGraph(int size);
    void AddEdge(int node1, int node2, int weight);
    vector<Edge> Find_Nearnodes(int node);
    int DijkstraDistance(int start, int end);
    int BellmanFordDistance(int start, int end);
    vector<vector<int>> FloydWarshallDistance();
private:
    vector<vector<Edge>> nodes;
};
//인접 리스트로 그래프를 구현

UndirectedGraph::UndirectedGraph(int size) {
    for (int i = 0; i < size; i++) {
        nodes.push_back(vector<Edge>());
    }
    //nodes 벡터 크기를 초기화, size만큼 돌면서 빈 Edge 벡터를 삽입
}

void UndirectedGraph::AddEdge(int node1, int node2, int weight) {
    nodes[node1].push_back(Edge(node2, weight));
    //인접리스트 nodes의 [node1]번 노드에 간선 정보 삽입
}

vector<Edge> UndirectedGraph::Find_Nearnodes(int node) {
    vector<Edge> nearNodes;
    return nearNodes = nodes[node];
    //해당 노드와 연결된 노드와 간선정보를 전부 담아서 리턴
}

int UndirectedGraph::DijkstraDistance(int start, int end) {
    vector<int> dist(nodes.size(), -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    //우선순위 큐(최대 Heap과 같음) <자료형, 구현체(기본이 벡터라고함), 오름차순>

    dist[start] = 0;
    //dist[i] 는 start 노드로 부터 i 노드 까지의 거리를 저장하는 벡터
    pq.push(pair<int, int>(0, start));
    //우선순위 큐에 시작 노드를 0으로 push
    while (!pq.empty()) {
        int curr = pq.top().second;
        pq.pop();
        //현재 노드를 curr에 담고 pop, 가장 가중치가 작은 노드가 curr에 담김
        for (auto it : nodes[curr]) {
            int next = it.target_node;
            int cost = it.weight;
            //현재 노드에 들어있는 간선들을 보고 다음 노드와 가중치를 본다.
            if (dist[next] < 0 || dist[next] > dist[curr] + cost) {
                //다음 노드가 경로 값 업데이트가 되지 않은 노드거나, 
                //현재 노드와 가중치를 합한 값이 다음 노드의 경로 값보다 작다면
                dist[next] = dist[curr] + cost;
                pq.push(pair<int, int>(dist[next], next));
                //경로 값을 업데이트하고 우선순위 큐에 push
            }
        }
    }
    return dist[end];
    //O(E logE) 199 log199 3 200
}

vector<vector<int>> UndirectedGraph::FloydWarshallDistance() {
    const int inf = 987654321;
    int MAX = nodes.size();
    vector<vector<int>> dists(MAX, vector<int>(MAX, inf));

    for (int i = 0; i < MAX; i++) {
        dists[i][i] = 0;
    }
    for (int i = 0; i < MAX; i++) {
        for (auto it : nodes[i]) {
            dists[i][it.target_node] = it.weight;
        }
    }

    //최소경로는 항상 k분기점을 지나간다고 가정햇을때
    for (int k = 0; k < MAX; k++) {
        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                dists[i][j] = min(dists[i][j], dists[i][k] + dists[k][j]);
            }
        }
    }

    return dists;
    //O(V^3) max 200 200 200
}

int UndirectedGraph::BellmanFordDistance(int start, int end) {
    const int inf = 987654321;
    vector<int> dist(nodes.size(), inf);
    dist[start] = 0;

    //최단 경로는 n-1개의 edge로 구성 -> n-1번 루프를 돈다
    for (int i = 0; i < nodes.size() - 1; i++) {
        //모든 노드에 대해서 최단 거리를 갱신
        for (int curr = 0; curr < nodes.size(); curr++) {
            if (dist[curr] < inf) {
                for (auto it : nodes[curr]) {
                    int next = it.target_node;
                    int cost = it.weight;
                    dist[next] = min(dist[next], dist[curr] + cost);
                }
            }
        }
    }
    return dist[end];
    //O(VE) max 200 E 3 200
}

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    int answer = 0;
    UndirectedGraph mGraph = UndirectedGraph(n);
    for (int i = 0; i < fares.size(); i++) {
        mGraph.AddEdge(fares[i][0] - 1, fares[i][1] - 1, fares[i][2]);
        mGraph.AddEdge(fares[i][1] - 1, fares[i][0] - 1, fares[i][2]);
    }
    //그래프를 구성

    vector<vector<int>> FWres = mGraph.FloydWarshallDistance();
    //전체 그래프에 대해서 최소경로가 나옴

    int a_min = FWres[s - 1][a - 1];
    int b_min = FWres[s - 1][b - 1];
    int min_dist = a_min + b_min;

    //시작 노드에서 a와 b로 가는 최소 경로값을 구한다.

    vector<bool> Check(n, false);
    Check[s - 1] = true;

    for (int i = 0; i < Check.size(); i++) {
        if (Check[i] == false) {
            int a_min2 = FWres[i][a - 1];
            int b_min2 = FWres[i][b - 1];
            int node_min = FWres[s - 1][i];
            int tmp = abs(a_min2 + b_min2 + node_min);
            min_dist = min(min_dist, tmp);
        }
    }

    answer = min_dist;
    return answer;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    vector<vector<int>> fare = { {2, 6, 6} ,{6, 3, 7},{4, 6, 7},{6, 5, 11 }, { 2, 5, 12 }, { 5, 3, 20 }, { 2, 4, 8 }, { 4, 3, 9 } };
    cout << solution(6, 4, 5, 6, fare);
}
