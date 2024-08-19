/*
    思路： 拓扑排序，时间On²，空间On
    1. 这里利用umap实现了，也可以使用vector，前提是在知道具体的点的数量的时候
*/

#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    unordered_map<int, int> ind;    // 记录每个点的入度
    unordered_map<int, vector<int>> edges;  // value为以key为弧尾的边的集合
    queue<int> zero_queue;      // 当前入度为0的所有的点

    while (m --) {
        int x, y;       // x -> y
        cin >> x >> y;
        edges[x].push_back(y);  // x指向y
        if (!ind.count(x)) {    // 如果x没有使用过，初始化其入度为0
            ind[x] = 0;
        }
        ++ ind[y];  // y的入度+1
    }

    for (auto& it : ind) {  // 遍历所有节点的入度，找到入度为0的点入队
        if (it.second == 0) {
            zero_queue.push(it.first);
        }
    }

    vector<int> res;

    while (zero_queue.size()) { // 将所有入度为0的点出队完才算
        int zero_point = zero_queue.front();    // 队头出队
        zero_queue.pop();
        res.emplace_back(zero_point);
        auto& edge_vec = edges[zero_point];
        for (auto& point : edge_vec) {  // 将其指向的点的入度-1
            -- ind[point];
            if (ind[point] == 0) {  // 如果某个点的入度减为了0
                zero_queue.push(point); // 将这个点入队
            }
        }
    }

    if (res.size() < n) {   // 如果没有全部出队，则不存在结果
        cout << -1 << endl;
        return 0;
    }

    for (auto& num : res) {
        cout << num << " ";
    }
    
    return 0;
}