/*
    思路： dp，时间Onv，空间Onv，可优化到On
    dp[i][j]表示使用前i个物品，装满体积为j的背包的最大价值
    1. 每次选择，可以判断，只取前i-1个物品，体积为j的最大价值
    2. 只取前i-1个物品，再取多个个第i个物品，二者间的最大价值
    优化的思路不在本题，方法就是第三层循环从s变成logs，利用二进制计数优化物品个数的枚举次数，从而转变成01背包问题，还可以空间优化
*/

#include <iostream>
#include <algorithm>

using namespace std;

const int N = 110;

int n, m;               // 物品数，背包体积
int v[N], w[N], s[N];   // 体积，价值，数量
int dp[N][N];

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++ i) {
        cin >> v[i] >> w[i] >> s[i];
    }
    for (int i = 1; i <= n; ++ i) {
        for (int j = 0; j <= m; ++ j) {
            for (int k = 0; k <= s[i] && k * v[i] <= j; ++ k) { // 第i个物品，取k个，不超过个数，且体积合适
                dp[i][j] = max(dp[i][j], dp[i - 1][j - v[i] * k] + w[i] * k);   // 取i-1个物品的最大价值加上取k个的最大价值
            }
        }
    }
    cout << dp[n][m] << endl;
    return 0;
}