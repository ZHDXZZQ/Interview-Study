/*
    思路：完全背包DP解法，时间On²，空间On
    状态表示：f[i][j]表示只从1~i中选，且总和等于j的方案数
    状态转移方程：f[i][j] = f[i - 1][j] + f[i][j - i];  
    表示的是总和为j的数可以来自于1~i-1种选的数字的和 + 1~i中选的数字构成的和为j - i再选上i
    类似跳台阶，加上这个数不算是新的解法，但是两个解法要加起来就算是更多的解法了
    优化成一维空间即可
*/

#include <iostream>
#include <vector>

using namespace std;

const int mod = 1e9 + 7;

int main() {
    int n;
    cin >> n;
    vector<int> dp(n + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= n; ++ i) {     // i表示当前这轮对所有数计算上一个数是当前数-i的解法，即上一轮x种方法得到x，这轮的j=x+i，是一种方法得到的j
        for (int j = i; j <= n; ++ j) { // 对于每个间隔i，遍历所有数，为每次不同方法的和
            dp[j] = (dp[j] + dp[j - i]) % mod;
        }
    }
    cout << dp[n];
    return 0;
}