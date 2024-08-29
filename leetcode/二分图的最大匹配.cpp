/*
    思路： 匈牙利算法dfs，时间On1*m，空间On1+n2+m
    最坏情况下，每个点都要让另外的点深度遍历，相当于每次都遍历所有边
    前提已经是二分图，这道题非常精妙
    1. 对于每个左边的点，优先选择连接的点中第一个可以匹配的点匹配
    2. 如果对方点还没有匹配，那么匹配成功
    3. 如果对方点已经匹配，那么让对方点现在匹配的点换一个看看是否能匹配，如果可以，这两个匹配成功。
    4. 如果不可以，则再去找下一个连接的点
    5. 如果都不可以匹配，则返回false
    相当于每个点都会做所有的尝试，又可以驱动要改变的点继续做尝试
*/

#include <iostream>
#include <vector>
// #include <cstring>

using namespace std;

int n1, n2, m;
int u, v;
vector<vector<int>> adj;    // 邻接表，存储左边点对应的右边点的连线
vector<int> match;  // 记录对于右边的n2的点，所匹配的n1的点的值
vector<bool> used;  // 记录当前左边点已经尝试过的匹配的点

bool find(int i) {
    for (auto& next : adj[i]) { // 遍历这个点的所有邻居
        if (used[next] == false) {  // 如果该点还没遍历过
            used[next] = true;
            if (match[next] == -1 || find(match[next])) {   // 如果该点没有匹配的点，或者已经有匹配的点但是匹配的点还能找到新的右边匹配的点
            // 不用担心重复遍历，因为这个点已经被置为true
                match[next] = i;    // 这个右边的点和该点匹配成功
                return true;
            }
        }
    }
    // 都没有匹配的，该点匹配失败
    return false;
}

int main() {
    cin >> n1 >> n2 >> m;
    adj = vector<vector<int>>(n1);
    match = vector<int>(n2, -1);
    used = vector<bool> (n2, false);
    while (m --) {
        cin >> u >> v;
        adj[u - 1].push_back(v - 1);
    }
    int res = 0;
    for (int i = 0; i < n1; ++ i) { // 遍历每个左边的点
        used = vector<bool>(n2, false); // 初始化表示都还没有尝试
        // memset(used, false, sizeof used);
        if (find(i)) {  // 如果能找到一个合适的点
            ++ res; // 结果+1
        }
    }
    cout << res;
    return 0;
}