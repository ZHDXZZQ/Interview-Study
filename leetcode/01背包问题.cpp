/*
    思路： dp，时间Onv，空间Onv，可优化到On
    dp[i][j]表示使用前i个物品，装满体积为j的背包的最大价值
    1. 每次选择，可以判断，只取前i-1个物品，体积为j的最大价值
    2. 只取前i-1个物品，再取一个第i个物品，二者间的最大价值
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, v;
    cin >> n >> v;
    vector<int> volumes(n + 1), values(n + 1);
    for (int i = 1; i <= n; ++ i) {
        cin >> volumes[i] >> values[i];
    }
    vector<vector<int>> dp(n + 1, vector<int> (v + 1, 0));
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= v; ++ j) {
            dp[i][j] = dp[i - 1][j]; // 即取第i个物品，或不取，求最大价值
            if (j >= volumes[i]) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - volumes[i]] + values[i]);    // 需要先把第i个的空间腾出来，再拿第i个物品
            }
        }
    }
    cout << dp[n][v] << endl;
    return 0;
}



// 使用滚动数组优化：因为一维的i只用到了i-1，因此把一维优化掉，利用滚动数组，实现空间Ov的情况
// #include <iostream>
// #include <vector>
// #include <algorithm>

// using namespace std;

// int main() {
//     int n, v;
//     cin >> n >> v;
//     vector<int> volumes(n + 1), values(n + 1);
//     for (int i = 1; i <= n; ++ i) {
//         cin >> volumes[i] >> values[i];
//     }
//     vector<int> dp(v + 1, 0);
//     for (int i = 1; i <= n; ++ i) {
//         for (int j = v; j >= volumes[i]; -- j) {
//             dp[j] = max(dp[j], dp[j - volumes[i]] + values[i]);
//         }
//     }
    
//     cout << dp[v] << endl;
//     return 0;
// }