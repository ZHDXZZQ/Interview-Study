/*
    思路： SG函数博弈论，时间Onm，空间Om+M
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <unordered_set>

using namespace std;

const int N = 110, M = 10010;  // N 和 M 分别表示最大物品数和最大堆数

int n, m;
int s[N], f[M];  // s 数组存储可行操作数集合，f 数组存储已计算的 SG 函数值

// SG 函数，计算状态 x 的 SG 值
int sg(int x) {
    if (f[x] != -1) {  // 如果 SG 值已被计算，直接返回
        return f[x];
    }

    unordered_set<int> S;  // 集合 S 用于记录可能的 SG 值
    for (int i = 0; i < m; ++ i) {
        int sum = s[i];  // s[i] 表示可以从当前状态移走的数量
        if (x >= sum) {  // 只有当当前状态大于或等于 s[i] 时才能移走
            S.insert(sg(x - sum));  // 递归计算 sg(x - sum) 的 SG 值，并插入集合
        }
    }

    // 找到最小的非负整数（Mex），不在集合 S 中的那个值，即当前状态的 SG 值
    for (int i = 0;; ++ i) {
        if (!S.count(i)) {
            return f[x] = i;  // 记录并返回 SG 值
        }
    }
}

int main() {
    cin >> m;  // 输入可行操作数的数量
    for (int i = 0; i < m; ++ i) {
        cin >> s[i];  // 输入每种操作可以移走的数量
    }
    cin >> n;  // 输入游戏中有多少堆物品

    memset(f, -1, sizeof f);  // 初始化 SG 值数组为 -1，表示尚未计算过

    int res = 0;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;  // 输入每一堆物品的数量
        res ^= sg(x);  // 对每堆的 SG 值进行异或操作
    }

    // 最终判断胜负
    if (res) {
        puts("Yes");  // 异或结果不为 0，先手必胜
    } else {
        puts("No");  // 异或结果为 0，先手必败
    }
    return 0;
}
