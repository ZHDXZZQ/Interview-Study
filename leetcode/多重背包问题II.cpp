/*
    思路： dp，时间Onv，空间Onv，可优化到On
    dp[i][j]表示使用前i个物品，装满体积为j的背包的最大价值
    1. 每次选择，可以判断，只取前i-1个物品，体积为j的最大价值
    2. 只取前i-1个物品，再取多个个第i个物品，二者间的最大价值
    优化的思路就是第三层循环从s变成logs，利用二进制计数优化物品个数的枚举次数，同时空间可以降维
*/

#include <iostream>
#include <algorithm>

using namespace std;

const int N = 25000, M = 2010;

int n, m;         // 物品种类数，背包体积
int v[N], w[N];   // 体积，价值
int dp[N];

int main() {
    cin >> n >> m;
    int cnt = 0;
    for (int i = 1; i <= n; ++ i) {
        int a, b, s;    // 这个物品的体积，价值，数量
        cin >> a >> b >> s;
        int k = 1;  // k从1开始
        while (k <= s) {
            ++ cnt;
            v[cnt] = a * k; // 第cnt个物品不再是i，而是改变为k个物品i，这样就转化成了01背包问题，变成了多件物品，每个物品可以取0或1个了
            w[cnt] = b * k;
            s -= k;     // 物品个数减去当前合成的个数
            k *= 2;     // k翻倍增长
        }
        if (s > 0) {    // 如果最后一波还有剩余
            ++ cnt;     // 存入
            v[cnt] = a * s;
            w[cnt] = b * s;
        }   // 然后对下一个物品同样融合
    }
    n = cnt;
    for (int i = 1; i <= n; ++ i) {
        for (int j = m; j >= v[i]; -- j) {
            dp[j] = max(dp[j], dp[j - v[i]] + w[i]);
        }
    }
    cout << dp[m] << endl;
    return 0;
}