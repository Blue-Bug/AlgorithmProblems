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
//Edge ����ü -> �̾��� ���� ����ġ ������ ����ִ�.

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
//���� ����Ʈ�� �׷����� ����

UndirectedGraph::UndirectedGraph(int size) {
    for (int i = 0; i < size; i++) {
        nodes.push_back(vector<Edge>());
    }
    //nodes ���� ũ�⸦ �ʱ�ȭ, size��ŭ ���鼭 �� Edge ���͸� ����
}

void UndirectedGraph::AddEdge(int node1, int node2, int weight) {
    nodes[node1].push_back(Edge(node2, weight));
    //��������Ʈ nodes�� [node1]�� ��忡 ���� ���� ����
}

vector<Edge> UndirectedGraph::Find_Nearnodes(int node) {
    vector<Edge> nearNodes;
    return nearNodes = nodes[node];
    //�ش� ���� ����� ���� ���������� ���� ��Ƽ� ����
}

int UndirectedGraph::DijkstraDistance(int start, int end) {
    vector<int> dist(nodes.size(), -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    //�켱���� ť(�ִ� Heap�� ����) <�ڷ���, ����ü(�⺻�� ���Ͷ����), ��������>

    dist[start] = 0;
    //dist[i] �� start ���� ���� i ��� ������ �Ÿ��� �����ϴ� ����
    pq.push(pair<int, int>(0, start));
    //�켱���� ť�� ���� ��带 0���� push
    while (!pq.empty()) {
        int curr = pq.top().second;
        pq.pop();
        //���� ��带 curr�� ��� pop, ���� ����ġ�� ���� ��尡 curr�� ���
        for (auto it : nodes[curr]) {
            int next = it.target_node;
            int cost = it.weight;
            //���� ��忡 ����ִ� �������� ���� ���� ���� ����ġ�� ����.
            if (dist[next] < 0 || dist[next] > dist[curr] + cost) {
                //���� ��尡 ��� �� ������Ʈ�� ���� ���� ���ų�, 
                //���� ���� ����ġ�� ���� ���� ���� ����� ��� ������ �۴ٸ�
                dist[next] = dist[curr] + cost;
                pq.push(pair<int, int>(dist[next], next));
                //��� ���� ������Ʈ�ϰ� �켱���� ť�� push
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

    //�ּҰ�δ� �׻� k�б����� �������ٰ� ����������
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

    //�ִ� ��δ� n-1���� edge�� ���� -> n-1�� ������ ����
    for (int i = 0; i < nodes.size() - 1; i++) {
        //��� ��忡 ���ؼ� �ִ� �Ÿ��� ����
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
    //�׷����� ����

    vector<vector<int>> FWres = mGraph.FloydWarshallDistance();
    //��ü �׷����� ���ؼ� �ּҰ�ΰ� ����

    int a_min = FWres[s - 1][a - 1];
    int b_min = FWres[s - 1][b - 1];
    int min_dist = a_min + b_min;

    //���� ��忡�� a�� b�� ���� �ּ� ��ΰ��� ���Ѵ�.

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
