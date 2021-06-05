#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

struct fish {
    int row, col, size;
};

struct sort_fish {
    fish intel;
    int dist;
};
//움직일때마다 스캔을 해서 조건에 맞는 물고기를 먹으러간다.
struct cmp {
    bool operator()(sort_fish a, sort_fish b) {
        if (a.dist == b.dist) {
            if (a.intel.row == b.intel.row) {
                return a.intel.col > b.intel.col;
            }
            return a.intel.row > b.intel.row;
        }
        return a.dist > b.dist;
    }
};
priority_queue<sort_fish, vector<sort_fish>, cmp> pq;

int bfs(fish babyshark) {
    int cnt = 0;
    queue<sort_fish> q;
    while (!pq.empty()) {
        sort_fish tmp = pq.top();
        pq.pop();
        if (tmp.intel.size > babyshark.size) {
            q.push(tmp);
            continue;
        }
    }
}

int main() {
    int n, tmp;
    fish babyshark;
    vector<fish> feed;
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> tmp;
            if (tmp == 9) {
                babyshark = fish{ i,j,2 };
            }
            else if (tmp != 0) {
                feed.push_back(fish{ i,j,tmp });
            }
        }
    }
    if (feed.size() == 0) {
        cout << 0;
        return 0;
    }
    for (auto it : feed) {
        pq.push(sort_fish{ it,
            abs(it.col - babyshark.col) + abs(it.row - babyshark.row) });
    }
}