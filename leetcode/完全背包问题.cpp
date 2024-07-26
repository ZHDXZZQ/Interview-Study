/*
    思路： dp，时间Onv，空间Onv，可优化到On
    dp[i][j]表示使用前i个物品，装满体积为j的背包的最大价值
    1. 每次选择，可以判断，只取前i-1个物品，体积为j的最大价值
    2. 只取前i-1个物品，再取多个个第i个物品，二者间的最大价值
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    int n, v;
    cin >> n >> v;
    vector<int> vol(n + 1), value(n + 1);
    for (int i = 1; i <= n; ++ i) {
        cin >> vol[i] >> value[i];
    }
    
    // 优化前，超时
    // vector<vector<int>> dp(n + 1, vector<int> (v + 1, 0));
    // for (int i = 1; i <= n; ++ i) {
    //     for (int j = 1; j <= v; ++ j) {
    //         // dp[i][j] = dp[i - 1][j]; 
    //         // 这里没必要写，因为已经包含在下面的dp[i - 1][j - k * vol[i]] + value[i] * k中，这里的下标关系一定搞明白
    //         // 如果k从1开始，就需要这一行，有了这行的时候下面的dp[i-1]可以变成dp[i]
    //         for (int k = 0; k * vol[i] <= j; ++ k) {
    //             dp[i][j] = max(dp[i][j], dp[i - 1][j - k * vol[i]] + value[i] * k);
    //         }
    //     }
    // }
    // cout << dp[n][v] << endl;
    
    
    // 优化1，减少内层循环，利用公式差，实际上也计算了每个物品取n次时的情况
    // vector<vector<int>> dp(n + 1, vector<int> (v + 1, 0));
    // for (int i = 1; i <= n; ++ i) {
    //     for (int j = 1; j <= v; ++ j) {
    //         dp[i][j] = dp[i - 1][j]; // 不拿当前第i个情况下的最大价值
    //         if (j >= vol[i]) {
    //             dp[i][j] = max(dp[i][j], dp[i][j - vol[i]] + value[i]);  // 拿多个第i个物品的最大价值
    //         }
    //     }
    // }
    // cout << dp[n][v] << endl;
    
    
    // 优化2：空间优化掉第一维
    // 为什么不用从后往前？因为我们要的是同一维度下，取不同个数的，而不是i-1维度的
    vector<int> dp(v + 1, 0);
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= v; ++ j) {
            if (j >= vol[i]) {
                dp[j] = max(dp[j], dp[j - vol[i]] + value[i]);
            }
        }
    }
    cout << dp[v] << endl;
    return 0;
}