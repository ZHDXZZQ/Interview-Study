/*
    思路： spfa算法，时间最坏是Omn，平均下来差不多Oxm，其中x是一个远小于n的常数，空间On+m
    最坏情况是负权边太多，进行了过多的松弛操作
    Shortest Path Faster Algorithm
    bellman_ford算法改进
    1. 每次遍历所有距离被更新为更小的边，更新由原点到b的最新最短距离，即如果原点到a的距离变短了，那么原点到b的距离也可以变短，是一个影响链
*/

#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;
using pii = pair<int, int>;

int n, m;
int a, b, w;

const int INF = 1e9;
vector<vector<pii>> edges;
vector<int> dist;

void spfa() {
    for (int i = 0; i < n; ++ i) {
        dist[i] = INF;
    }
    dist[0] = 0;        // 初始化原点到自身的距离为0
    queue<int> q;       // 队列中存储上一轮距离变小的点，只有变小的点才有意义去更新
    q.push(0);
    while (q.size()) {
        auto point = q.front();
        q.pop();
        for (auto& edge : edges[point]) {    // 遍历这个点能到达的所有点
            int& to = edge.first;       // 到达的点
            int& weight = edge.second;  // 距离
            int new_weight = dist[point] + weight;  // 计算新的距离
            if (new_weight < dist[to]) {        // 如果到达to点的距离可以更小
                q.push(to);     // 将to插入队列并更新到达to点的距离
                dist[to] = new_weight;
            }
        }
    }
}

int main() {
    cin >> n >> m;
    edges = vector<vector<pii>>(n);
    dist = vector<int>(n);
    for (int i = 0; i < m; ++ i) {  // 初始化邻接表
        cin >> a >> b >> w;
        if (a == b) {   // 自环不必考虑
            continue;
        }   // 题目中不存在负环，但可能有负权边，无需考虑
        edges[a - 1].emplace_back(make_pair(b - 1, w));
    }
    spfa();
    if (dist[n - 1] == INF) {
        puts("impossible");
    } else {
        cout << dist[n - 1] << endl;
    }
    return 0;
}