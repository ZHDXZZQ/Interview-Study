/*
    思路： 迪杰斯特拉算法优化：时间Omlogn（感觉像是Omnlogn啊？空间Om+n
    1. 每次选择当前到起点最近的点为中转节点，记录每个节点以该节点为中转的路径到达起点的最小值
    2. 继续选择下一个最近的节点重复上述步骤，直到所有节点都中转过
    具体细节看注释
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;
using pii = pair<int, int>;

const int INF = 1e9;
int n, m;
int x, y, z;

int dijkstra(vector<vector<pii>>& adj) {
    vector<int> dis(n, INF);    // 每个点到原点的距离，初始化为INF
    vector<bool> used(n, false);    // 是否已某个点为中转计算过，计算过的点为true
    dis[0] = 0; // 初始化原点到自己的距离为0
    priority_queue<pii, vector<pii>, greater<pii>> heap;    // 小根堆，根据first排序，first为距离，second为节点下标
    heap.push({0, 0});
    int cnt = 0;
    while (cnt < n && heap.size()) {   // 如果堆不空，或者还没有取出过n个点
        int select = heap.top().second; // 选取堆顶，即当前距离原点最短距离的点
        heap.pop();
        
        if (used[select]) { // 如果已经遍历过，跳过
            continue;
        }
        used[select] = true;    // 否则遍历这个点，遍历个数+1
        ++ cnt;
        
        for (auto& point : adj[select]) {    // 遍历这个点能到达的所有点
            int& to = point.first;       // 到达的点
            int& weight = point.second;  // 距离
            
            if (dis[to] > dis[select] + weight) {   // 如果当前这个点到原点的距离比经过select中转更远的话
                dis[to] = dis[select] + weight;     // 更新这个点到原点的距离，更短的距离
                if (!used[to]) {        // 如果这个点还没有被遍历过，则之后可能作为中转节点
                    heap.push({dis[to], to});           // 将这个点及其到原点的距离插入
                }
            }
        }
    }
    
    return dis[n - 1] == INF ? -1 : dis[n - 1]; // 如果终点到起点为INF，则不可达，否则返回最短路径
}

int main() {
    cin >> n >> m;
    vector<vector<pii>> adj(n); // 邻接表代替邻接矩阵，稀疏图使用
    
    for (int i = 0; i < m; ++i) {
        cin >> x >> y >> z;
        if (x != y) {   // 去除自环
            adj[x - 1].emplace_back(y - 1, z);  // 插入有向边x到y点的距离，不用考虑是否更短
        }
    }
    
    cout << dijkstra(adj) << endl;
    return 0;
}
