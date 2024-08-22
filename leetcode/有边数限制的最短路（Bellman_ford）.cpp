/*
    思路： 贝尔曼-弗尔德算法，时间Omk+n，空间On+m
    类似迪杰斯特拉算法，这里存在负权边，可能存在自环和负环，可能存在重边
    1. 最多走k次，每次更新一遍所有数组，可以判断是否有负环，但是不影响结果
    2. 每次遍历所有边，更新由原点到b的最新最短距离，即如果原点到a的距离变短了，那么原点到b的距离也可以变短，是一个影响链
*/

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int n, m, k;
int a, b, w;

struct edge {   // 边，a到b的距离为w
    int a, b, w;
};

const int INF = 1e9;
vector<edge> edges;
vector<int> dist;
vector<int> last;

void bellman_ford() {
    for (int i = 0; i < n; ++ i) {
        dist[i] = INF;
    }
    dist[0] = 0;        // 初始化原点到自身的距离为0
    while (k --) {      // 最多走k条路
        last = dist;    // 存储上一次的结果，避免本轮更新被本轮影响
        for (int i = 0; i < m; ++ i) {
            auto& edge = edges[i];
            dist[edge.b] = min(dist[edge.b], last[edge.a] + edge.w);    // 遍历根据a做中转，原点到b的最短距离是否能更短，是否有更新
        }
    }
}

int main() {
    cin >> n >> m >> k;
    edges = vector<edge>(m);
    dist = vector<int>(n);
    last = vector<int>(n);
    for (int i = 0; i < m; ++ i) {  // 初始化
        cin >> a >> b >> w;
        edges[i].a = a - 1;
        edges[i].b = b - 1;
        edges[i].w = w;
    }
    bellman_ford();
    if (dist[n - 1] > INF / 2) {
        puts("impossible");
    } else {
        cout << dist[n - 1] << endl;
    }
    return 0;
}