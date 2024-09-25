/*
    思路： 状态压缩DP，时间O(n^2 * 2^n)，空间O(n * 2^n + n^2)
    暴搜的复杂度为n！约为10^18次
    dp[i][j]中的i为二进制数，代表每一个点是否经过，j代表当前的终点。即为从0到j经过了i中为1的点的最短路径
    通过倒数第二个到达点+倒数第二个点到j点的距离来更新这个值，注意控制i的值
*/

#include <iostream>
#include <vector>

using namespace std;
const int INF = 1e9;

int main() {
    int n;
    cin >> n;
    int m = 1 << n;
    vector<vector<int>> dist(n, vector<int>(n));
    vector<vector<int>> dp(m, vector<int>(n, INF));
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            cin >> dist[i][j];
        }
    }
    dp[1][0] = 0;   // 起点，站在0点，经过0点的最短距离为0

    for (int i = 0; i < m; ++ i) {  // 枚举所有状态，枚举所有点
        for (int j = 0; j < n; ++ j) {
            if (i >> j & 1) {   // 当前的状态经过了j点
                for (int k = 0; k < n; ++ k) {
                    if (i >> k & 1) {   // 当前的状态也经过了k点
                        dp[i][j] = min(dp[i][j], dist[k][j] + dp[i - (1 << j)][k]);
                        // 更新之前的从0到k点不经过j的最短路径加上k到j的距离，和当前经过kj到j的最短路径的值
                    }
                }
            }
        }
    }

    cout << dp[m - 1][n - 1] << endl;
    return 0;
}