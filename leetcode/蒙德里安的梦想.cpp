/*
    思路： 状态压缩DP，时间Om*4^n，空间O2^n
    1. 对于每一列，考虑上一列对该列伸出的行，伸出的部分用1表示，因此对于每一列的n个行，可以用一个n位的二进制数表示
    2. 对于每种情况，我们需要知道是否符合要求，我们可以优先考虑横着放，然后剩下的空格竖着放（需要判断是否能竖着放），每种情况都做考虑
    3. 要保证每一列都能放满
*/

#include <iostream>
#include <vector>

using namespace std;

long long calc(int& n, int& m) {
    vector<vector<long long>> dp(m + 1, vector<long long>(1 << n, 0));  // dp[i][j]表示，对于第i列，前面一列的各行对本列的各行利用二进制数j来表示
    vector<bool> state_is_valid(1 << n, false); // 记录对于第i种状态是否可行，即第i种状态的空出的连续行是不是奇数个格子，奇数个格子无法竖着放
    vector<vector<int>> state(1 << n);  // 记录对应第i种状态，能够组合的所有状态

    for (int i = 0; i < 1 << n; ++ i) { // 先遍历所有状态
        int cnt = 0;    // 记录连续0的个数
        bool is_valid = true;   // 记录该状态是否合法
        for (int j = 0; j < n; ++ j) {  // 遍历该状态的每一行
            if (i >> j & 1) {   // 如果该行为1，代表这行被占用
                if (cnt & 1) {  // 如果前面的空格是奇数个
                    is_valid = false;   // 不合法
                    break;
                } else {
                    cnt = 0;    // 如果合法则继续开始下一轮记录
                }
            } else {
                ++ cnt; // 如果是空格，个数+1
            }
        }
        if (cnt & 1) {  // 如果最后一部分的连续空格是奇数个
            is_valid = false;   // 也不合法
        }
        state_is_valid[i] = is_valid;   // 记录这种状态是否合法
    }

    for (int i = 0; i < 1 << n; ++ i) { // 遍历所有状态
        for (int j = 0; j < 1 << n; ++ j) { // 遍历所有状态
            if ((i & j) == 0 && state_is_valid[i | j]) {    // 先判断横着放i&j，如果==0，说明这两种状态横着插没问题。后面判断插完之后能否竖着放满，如果放不满则这两个状态不行
                state[i].push_back(j);  // 如果横着放可以，竖着也能补充，则把这个状态插入对应状态中，表示对于状态i，可以采用状态j的方法
            }
        }
    }

    dp[0][0] = 1;   // 初始化第0列的没有格子突出的状态为1
    for (int i = 1; i <= m; ++ i) { // 遍历所有列
        for (int j = 0; j < 1 << n; ++ j) { // 遍历本列的所有状态
            for (auto& ok_state : state[j]) {   // 对于本列所能适配的所有状态
                dp[i][j] += dp[i - 1][ok_state];    // 本列的对应状态可以加上前一列的对应适配状态
            }
        }
    }

    return dp[m][0];    // 返回最后一列没有突出的情况
}

int main() {
    int n, m;
    cin >> n >> m;
    while (n || m) {
        cout << calc(n, m) << endl;
        cin >> n >> m;
    }
    return 0;
}