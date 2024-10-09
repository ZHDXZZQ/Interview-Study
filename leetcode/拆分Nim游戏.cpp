/*
    思路： SG的Mex博弈论， 时间On * N²，空间ON²
*/
#include <cstring>
#include <iostream>
#include <algorithm>
#include <unordered_set>

using namespace std;

const int N = 110;  // 定义最大状态数为 110

int n;  // 输入局面数量
int f[N];  // SG 值数组，f[x] 表示状态 x 的 SG 值

// 计算 SG 函数，状态 x 的 SG 值
int sg(int x) {
    if (f[x] != -1) {  // 如果 SG 值已经计算过，直接返回
        return f[x];
    }

    unordered_set<int> S;  // 集合 S 存储可能的 SG 值
    // 枚举所有可能的子状态组合
    for (int i = 0; i < x; ++ i) {
        for (int j = 0; j <= i; ++ j) {
            S.insert(sg(i) ^ sg(j));  // 子状态 i 和 j 的 SG 值异或后加入集合 S
        }
    }

    // Mex 操作：找出最小的非负整数，不在集合 S 中
    for (int i = 0;; ++ i) {
        if (!S.count(i)) {  // 找到 Mex 值
            return f[x] = i;  // 记录 SG 值并返回
        }
    }
}

int main() {
    cin >> n;  // 输入游戏局面数

    memset(f, -1, sizeof f);  // 初始化 SG 值数组为 -1，表示未计算

    int res = 0;  // 初始化异或结果
    while (n --) {  // 处理每个局面
        int x;
        cin >> x;  // 输入当前局面的状态值
        res ^= sg(x);  // 异或累加 SG 值
    }

    // 根据异或结果判断胜负
    if (res) {
        puts("Yes");  // 异或结果不为 0，先手胜
    } else {
        puts("No");  // 异或结果为 0，后手胜
    }
    return 0;
}
