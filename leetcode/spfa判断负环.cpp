/*
    思路： spfa算法，时间Omn，空间Om+n
    Shortest Path Faster Algorithm，bellman_ford算法改进
    1. 每次遍历所有距离被更新为更小的边，更新由原点到b的最新最短距离，即如果原点到a的距离变短了，那么原点到b的距离也可以变短，是一个影响链
    2. 在没有负环的情况下，最短路径的最远距离是通过至多 n-1 条边达到的。所以到达的边数经过的节点数达到n的时候，一定是存在负环
    对于bellman ford算法，如果在在进行完n−1次松弛后，再进行一次额外的松弛操作。
    如果在这一步中仍然存在能够继续松弛的边（即找到一个边 (u, v) 使得 dist[v] > dist[u] + weight(u, v)），则说明图中存在负环。
*/
#include <iostream>
#include <vector>
#include <queue>

using namespace std;
using pii = pair<int, int>;

int n, m;
int a, b, w;

const int INF = 1e9;
vector<vector<pii>> edges;
vector<int> dist;
vector<int> cnt;
vector<bool> in_queue;  // 记录节点是否在队列中，一个优化点

bool spfa() {
    dist[0] = 0;        // 初始化原点到自身的距离为0
    queue<int> q;       // 队列中存储上一轮距离变小的点，只有变小的点才有意义去更新
    for (int i = 0; i < n; i ++ ) { // 要初始全部插入队列，因为有可能原点到达不了该负环
        in_queue[i] = true;
        q.push(i);
    }

    while (!q.empty()) {
        int point = q.front();
        q.pop();
        in_queue[point] = false;  // 出队列时标记为不在队列中
        int& point_cnt = cnt[point];

        for (auto& edge : edges[point]) {    // 遍历这个点能到达的所有点
            int& to = edge.first;       // 到达的点
            int& weight = edge.second;  // 距离
            int new_weight = dist[point] + weight;  // 计算新的距离
            if (new_weight < dist[to]) {        // 如果到达to点的距离可以更小
                dist[to] = new_weight;
                cnt[to] = point_cnt + 1;    // 更近到达该节点的最短路径中的节点数，最大为n

                if (cnt[to] >= n) {  // 如果某个点被更新超过n次，则存在负环
                    return true;
                }
                // 在遍历到to这个节点前，遇到更短路径时，距离还是会更新，但是不会重复插入这个节点，避免了重复更新
                if (!in_queue[to]) {  // 如果to点不在队列中，才将它加入队列
                    q.push(to);
                    in_queue[to] = true;
                }
            }
        }
    }
    return false;
}

int main() {
    cin >> n >> m;
    edges = vector<vector<pii>>(n);
    dist = vector<int>(n, INF);
    cnt = vector<int>(n, 0);
    in_queue = vector<bool>(n, false);  // 初始化队列状态为false

    for (int i = 0; i < m; ++i) {  // 初始化邻接表
        cin >> a >> b >> w;
        edges[a - 1].emplace_back(b - 1, w);    // 自环也要记录
    }

    if (spfa()) {
        cout << "Yes" << endl;  // 存在负环
    } else {
        cout << "No" << endl;   // 不存在负环
    }

    return 0;
}
