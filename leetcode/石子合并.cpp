/*
    思路： 区间dp，时间n^3，空间On²
    dp[i][j]表示从第i个石子，到第j个石子，合并所需要花费的最小价值
    1. 对于每个区间的最后一次合并，一定是有左边一个大块和右边一个大块合并，我们遍历每个位置将其分割为两个大块
    2. 计算每次左边大块和右边大块合并花费的价值，再加上本次合并的价值。
    3. 遍历该区间的所有情况，取最小值
    4. 对于每次合并，新增加的价值其实就是区间内所有数的和，可以采用前缀和记录
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> perfix_sum(n);
    for (int i = 0; i < n; ++ i) { cin >> perfix_sum[i]; }
    for (int i = 1; i < n; ++ i) { perfix_sum[i] += perfix_sum[i - 1]; }    // 初始化并计算前缀和
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int len = 2; len <= n; ++ len) {   // 每个区间的长度从2开始
        for (int i = 0; i <= n - len; ++ i) {   // 遍历所有可能的区间
            int l = i, r = i + len - 1; // 记录当前区间的左右端点
            dp[l][r] = 1e9; // 更新当前的值为最大值，方便min更新，但是默认值为0，因为首次合并前无需花费，即单个石头无开销
            for (int k = l; k < r; ++ k) {  // 用k分割当前区间，分别计算每个左右区间的合并，这样递归下去其实是最小的两个石子的多次和的最小值
                int merge_lr = dp[l][k] + dp[k + 1][r] + perfix_sum[r]; // 记录合并这两个区间的花销
                if (l != 0) { merge_lr -= perfix_sum[l - 1]; }  // 前缀和计算
                dp[l][r] = min(dp[l][r], merge_lr); // 更新该区间的最小花销
            }
        }
    }
    cout << dp[0][n - 1];   // 0 到 n - 1即合并全部石子的开销
    return 0;
}