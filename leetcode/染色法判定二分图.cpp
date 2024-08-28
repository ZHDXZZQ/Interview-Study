/*
    思路： bfs，染色，时间
    二分图：能够把图中所有的点分为两个集合，同一集合中的任意两点间不存在边
    染色法：每个点可以是1色或2色，一个边的两个端点应该都是不同的颜色，否则不是二分图
    奇数环：存在点数为奇数的环，存在奇数环的图一定不是二分图
    1. 每次从一个点将其相连的边都染不同的色，如果碰到已经染色的节点且和其相邻的节点颜色相同，则不是二分图
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, m;
int u, v;
vector<vector<int>> adj;
vector<int> colors;

int main() {
    cin >> n >> m;
    adj = vector<vector<int>>(n);
    colors = vector<int>(n, 0);

    // 构建邻接表
    while (m--) {
        cin >> u >> v;
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }

    // 遍历所有节点，处理可能不连通的图
    for (int i = 0; i < n; ++i) {
        if (colors[i] != 0) continue;  // 已经染色的节点跳过，前面已经被判断过了

        // 开始BFS，染色
        queue<int> q;
        q.push(i);
        colors[i] = 1;  // 第一个节点染为1

        while (!q.empty()) {    // 将其能连接到的所有节点都染色
            int current = q.front();
            q.pop();

            // 遍历相邻节点
            for (auto neighbor : adj[current]) {
                if (colors[neighbor] == 0) {  // 邻居未染色
                    colors[neighbor] = 3 - colors[current];  // 染成相反的颜色（1 -> 2, 2 -> 1）
                    q.push(neighbor);   // 将邻居插入，接着染色其相邻未染色的节点
                } else if (colors[neighbor] == colors[current]) {  // 相邻节点颜色相同，说明不是二分图
                    cout << "No";
                    return 0;
                }   // 如果相邻节点已经被染色且颜色不同，则不用管，因为前面一定对其相邻节点已经处理过，或者已经插入队列了
            }
        }
    }
    // 如果所有节点都能顺利遍历完，说明没有相邻节点颜色相同，是二分图
    cout << "Yes";
    return 0;
}
