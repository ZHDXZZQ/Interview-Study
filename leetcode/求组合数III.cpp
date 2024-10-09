/*
    思路： Lucas定理，时间Ologp.a * blogp，空间Ologp.a    logp.a代表以p为底的a的对数
*/

#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

// 快速幂函数，用于计算 a^k % p
// 时间复杂度 O(log k)
int qmi(int a, int k, int p) {
    int res = 1;
    // 使用二进制指数法求 a^k % p
    while (k) {
        // 如果当前 k 的二进制最低位是 1，则累乘 a
        if (k & 1) {
            res = (LL)res * a % p;
        }
        // 平方 a，并将 k 右移一位（即除以 2）
        a = (LL)a * a % p;
        k >>= 1;
    }
    return res;
}

// 计算组合数 C(a, b) % p
// 时间复杂度 O(b log p)，其中 b 是较小的组合数范围
int C(int a, int b, int p) {
    // 如果 b > a，那么组合数无效，返回 0
    if (b > a) {
        return 0;
    }

    int res = 1;
    // 计算组合数 C(a, b) = a! / (b!(a-b)!) % p
    // 使用循环计算公式 a! / (a-b)! 并乘以 b! 的逆元
    for (int i = 1, j = a; i <= b; ++ i, -- j) {
        // 计算 (a * (a-1) * ... * (a-b+1)) % p
        res = (LL)res * j % p;
        // 乘以 i! 的逆元，i! 的逆元通过快速幂求出 (i^(p-2) % p)
        res = (LL)res * qmi(i, p - 2, p) % p;
    }
    return res;
}

// 使用 Lucas 定理计算组合数 C(a, b) % p
// Lucas 定理适用于 a, b 都很大的情况，通过递归缩小组合数的规模
int lucas(LL a, LL b, int p) {
    // 当 a 和 b 都小于 p 时，直接使用普通的组合数公式计算
    if (a < p && b < p) {
        return C(a, b, p);
    }
    // 使用 Lucas 定理递归计算
    // C(a, b) % p = C(a % p, b % p) * C(a / p, b / p) % p
    return (LL)C(a % p, b % p, p) * lucas(a / p, b / p, p) % p;
}

int main() {
    int n;
    // 输入测试用例的个数
    cin >> n;

    while (n --) {
        LL a, b;
        int p;
        // 输入 a, b 和质数 p，计算 C(a, b) % p
        cin >> a >> b >> p;
        // 输出结果
        cout << lucas(a, b, p) << endl;
    }

    return 0;
}
