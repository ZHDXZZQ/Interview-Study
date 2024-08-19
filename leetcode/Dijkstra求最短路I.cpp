/*
    思路： 迪杰斯特拉算法，时间On²，空间On²，可以优化
    1. 每次选择当前到起点最近的点为中转节点，记录每个节点以该节点为中转的路径到达起点的最小值
    2. 继续选择下一个最近的节点重复上述步骤，知道所有节点都中转过
*/

#include <iostream>
#include <vector>

using namespace std;

const int INF = 1e9;

int dijkstra(int& n, vector<vector<int>>& edges) {
    bool used[n];       // 记录该点是否已经遍历过
    int distance[n];    // 记录起点到该点的距离
    for (int i = 0; i < n; ++ i) {
        distance[i] = INF;  // 初始化
        used[i] = false;
    }
    distance[0] = 0;    // 起点到起点的距离为0
    for (int i = 0; i < n; ++ i) {  // 遍历所有的点，要让所有的点都被判断过一遍
        int select = -1;
        for (int j = 0; j < n; ++ j) {  // 找到当前得到的，起点到该点的距离最短的点
            if (!used[j] && (select == -1 || distance[select] > distance[j])) {
                select = j;
            }
        }
        if (select == -1) {  // 如果没有找到该点，说明剩余的点均无法到达，无需继续
            break;
        }
        used[select] = true;    // 标记该点已遍历
        for (int j = 0; j < n; ++ j) {  // 遍历所有点，将其余所有点根据该点为中转更新最小值
            distance[j] = min(distance[j], distance[select] + edges[select][j]);    // 以select点位中转，计算从起点到j点的新最短距离，没有负权边
        }
    }
    if (distance[n - 1] == INF) {   // 如果无法到达终点，返回-1
        return -1;
    }

    return distance[n - 1]; // 返回起点到终点的最短距离
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> edges(n, vector<int>(n, INF));  // 邻接矩阵存边，初始化任意两点间的距离为正无穷
    while (m --) {
        int x, y, z;
        cin >> x >> y >> z;
        if (x == y) {
            edges[x - 1][y - 1] = 0;    // 自环设置为0
            continue;
        }
        edges[x - 1][y - 1] = min(edges[x - 1][y - 1], z);  // 存储边，因为可能有重边和自环，因此直接取重复边的最小值
    }
    cout << dijkstra(n, edges) << endl;
    return 0;
}