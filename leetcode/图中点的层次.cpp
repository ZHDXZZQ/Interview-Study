/*
    思路： bfs，时间On，空间On+m
    1. 利用队列存储每一轮的走到的下一个节点，步数为1
    2. 没走光一次当前队列，下一轮队列的步数+1
    3. 也可以利用数组存储起点到该点的距离，到达下一个点的距离+1即可
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<bool> used(n, false);    // 是否走过
    vector<vector<int>> adj(n);     // 邻接表
    if (n == 1 && m == 1) {         // 如果只有1个节点1条边，自环0步
        cout << 0;
        return 0;
    }
    while (m --) {
        int a, b;
        cin >> a >> b;
        adj[a - 1].push_back(b - 1);    // 插入边
    }
    queue<int> bfs;
    bfs.push(0);
    used[0] = true;
    int res = 0;        // 初始化队列
    while (bfs.size()) {    // 如果所有节点都走完还没到达，返回-1
        int cnt = bfs.size();   // 记录本层所有节点数
        while (cnt --) {    // 走光本层所有节点
            auto point = bfs.front();
            bfs.pop();
            for (auto& next : adj[point]) { // 找到下一层节点
                if (next == n - 1) {    // 如果到达终点，返回结果
                    cout << res + 1;
                    return 0;
                }
                if (!used[next]) {  // 如果没有被遍历过，插入队列
                    bfs.push(next);
                    used[next] = true;
                }
            }
        }
        ++ res; // 步数+1
    }
    cout << -1;
    return 0;
}