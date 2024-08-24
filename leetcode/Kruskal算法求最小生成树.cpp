/*
    思路： 克鲁斯卡尔算法，时间Omlogm，空间On+m
    1. 每次选择权值最小的边，如果不构成环，则加入到结果中
    2. 利用并查集判断是否成环，不能简单用数组判断，因为有可能是两个子连通
*/

#include <iostream>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;
using tiii = tuple<int, int, int>;

int n, m;
int u, v, w;
const int INF = 1e9;

priority_queue<tiii, vector<tiii>, greater<tiii>> heap; // 小根堆
vector<int> parent;

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void union_sets(int x, int y) { // 将x和y合并到一个集合中
    int root_x = find(x);
    int root_y = find(y);
    if (root_x != root_y) {
        parent[root_x] = root_y;
    }
}

int kruskal() {
    int res = 0;
    int edges_used = 0;
    while (heap.size()) {   // 每次取出当前权值最小的边
        auto [cur_w, cur_u, cur_v] = heap.top();
        heap.pop();
        if (find(cur_u) != find(cur_v)) {   // 如果这两个不在一个集合中，说明这条边不会构成环
            res += cur_w;   // 这条边加入结果中
            union_sets(cur_u, cur_v);   // 将这两个点归入当前结果集合中
            ++ edges_used;  // 结果的边+1
        }
    }
    if (edges_used != n - 1) {  // 最终一定是n-1条边，如果不是，返回-1
        return INF;
    }
    return res;
}

int main() {
    cin >> n >> m;
    parent.reserve(n);
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
    }   // 并查集初始化
    while (m --) {  // 边插入
        cin >> u >> v >> w;
        heap.push({w, u - 1, v - 1});
    }
    int res = kruskal();
    if (res == INF) {
        cout << "impossible" << endl;
    } else {
        cout << res << endl;
    }
    return 0;
}