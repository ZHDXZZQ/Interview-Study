/*
    思路： dfs，时间On²，空间On²
    1. 因为是无向无环图，因此需要考虑谁为父节点
    2. 先进行计算的当作父节点，父节点的子树节点和一定大于子节点
    3. 计算每个节点的子树节点和
    4. 遍历所有节点的子树，将该节点删除后，剩下的连通图就都是各子树，及其父节点所在的树
    5. 因此遍历每个节点，计算将其删除后，各子树的节点的最大值，以及父树节点的最大值
    6. 选取其中的最小值作为答案
*/

#include <iostream>
#include <vector>

using namespace std;

int n;
int a, b;
vector<vector<int>> adj;
vector<int> cnt;
vector<bool> used;

int dfs(int point) {    // 计算以point为根的所有子树的节点和
    used[point] = true; // 防止反向遍历
    int sum = 1;        // 初始化节点自身一个
    for (auto& next : adj[point]) { // 遍历所有能到达的节点
        if (!used[next]) {  // 如果没用过，那么可以作为子节点，如果用过了，那么就是父节点，因为dfs一定是从父到子
            sum += dfs(next);   // 加上每个子节点为根的树的节点数
        }
    }
    cnt[point] = sum;   // 当前节点为根的节点数
    return sum;
}

int main() {
    cin >> n;
    adj = vector<vector<int>>(n);   // 邻接表
    cnt = vector<int>(n);   // 记录每个节点为根的总结点数
    used = vector<bool>(n, false);  // 是否使用过
    for(int i = 0; i < n - 1; ++ i) {
        cin >> a >> b;
        adj[a - 1].push_back(b - 1);    // 无向边插入
        adj[b - 1].push_back(a - 1);
    }
    dfs(0); // 计算
    int res = 1e9;
    for (int i = 0; i < n; ++ i) {  // 遍历每个节点
        int son_sum = 0;
        int max_son = 0;
        for (auto& point : adj[i]) {
            if (cnt[point] < cnt[i]) {  // 如果值更小，表明是其子树，否则认作为父辈节点
                son_sum += cnt[point];  // 记录子节点的和
                max_son = max(max_son, cnt[point]); // 记录子节点各树的最大节点连通图
            }
        }
        max_son = max(n - son_sum - 1, max_son);    // 把这些节点数删去后，记录父节点所在树的剩余节点总和
        res = min(res, max_son);    // 记录最大值的更小的值
    }
    cout << res;
    return 0;
}