/*
    思路： 普利姆算法，时间On（max（n， m）），空间On+m
    1. 每次找到距离结果集合中最近的一条边，插入结果集，避免成环
*/

#include <iostream>
#include <vector>

using namespace std;
using pii = pair<int, int>;

vector<vector<pii>> edges;
vector<bool> used;      // 这个节点是否已经进入结果集
vector<int> dist;       // 每个节点距离结果集的距离

int n, m;
int u, v, w;
const int INF = 1e9;

int prim() {
    int res = 0;
    for (int i = 0; i < n; ++ i) {  // 遍历n次
        int select = -1;
        for (int j = 0; j < n; ++ j) {
            if (used[j] == false &&(select == -1 || dist[select] > dist[j])) {  // 选择出来当前没加入结果中的，距离结果集最近的一个点
                select = j;
            }
        }
        if (select == -1 || (i && dist[select] == INF)) {   // 如果这个点是起始点，那么是INF不用管，如果不是起始点但为INF，说明其余点不可达结果集
            return INF;
        }
        used[select] = true;
        if (i) {
            res += dist[select];    // 起始点不记录，剩余点记录权值，加入结果集
        }
        for (auto& edge : edges[select]) {  // 遍历每次加入的点的所有边，更新最短距离，意思是更新to节点到结果集的最短距离，看看是否变短了
            int& to = edge.first;
            int& weight = edge.second;
            dist[to] = min(dist[to], weight);
        }
    }
    return res;
}

int main() {
    cin >> n >> m;
    used = vector<bool>(n, false);
    edges.reserve(n);
    dist = vector<int>(n, INF); // 初始化
    while (m --) {
        cin >> u >> v >> w;
        edges[u - 1].push_back({v - 1, w}); // 对应的边集插入，无向图
        edges[v - 1].push_back({u - 1, w});
    }
    int res = prim();
    if (res == INF) {
        puts("impossible");
    } else {
        cout << res << endl;
    }
    return 0;
}