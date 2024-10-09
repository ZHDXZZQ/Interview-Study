/*
    思路： 阶乘预处理与快速幂算法，时间ONlogmod+n，空间ON
*/

#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 100010, mod = 1e9 + 7;

// 定义数组用于存储阶乘和阶乘的逆元
int fact[N], infact[N]; // 使用 infact[i] 存储 i! 的模逆元。为了计算逆元，利用了费马小定理

// 快速幂函数，用于计算 a^k % p
// 这个函数通过二进制分解指数来快速计算幂，时间复杂度为 O(log k)
int qmi(int a, int k, int p) {
    int res = 1;
    // 循环直到 k 为 0
    while (k) {
        // 如果当前 k 的二进制最低位是 1，那么将结果乘以 a
        if (k & 1) {
            res = (LL)res * a % p;
        }
        // 将 a 平方，k 右移一位（相当于除以 2）
        a = (LL)a * a % p;
        k >>= 1;
    }
    return res;
}

int main() {
    // 预处理阶乘和阶乘的逆元
    fact[0] = infact[0] = 1;
    // 计算阶乘和阶乘的逆元
    for (int i = 1; i < N; ++ i) {
        // 计算 fact[i] = i! % mod
        fact[i] = (LL)fact[i - 1] * i % mod;
        // 计算 infact[i] = i! 的逆元，使用费马小定理
        infact[i] = (LL)infact[i - 1] * qmi(i, mod - 2, mod) % mod;
    }

    int n;
    // 读取测试用例的个数
    scanf("%d", &n);
    while (n --) {
        int a, b;
        // 读取两个数 a 和 b，计算组合数 C(a, b)
        scanf("%d%d", &a, &b);
        // 计算 C(a, b) = fact[a] * infact[b] * infact[a - b] % mod
        printf("%d\n", (LL)fact[a] * infact[b] % mod * infact[a - b] % mod);
    }

    return 0;
}
