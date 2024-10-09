/*
    思路： 卡特兰数，C(2n, n) / (n + 1) ，时间On+logmod，空间O1
*/

#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 100010, mod = 1e9 + 7; // 定义常量 N 和模数 mod

// 快速幂计算 a^k % p，时间复杂度 O(log k)
int qmi(int a, int k, int p) {
    int res = 1; // 结果初始化为 1
    // 使用二进制指数法计算 a^k % p
    while (k) {
        if (k & 1) {
            res = (LL)res * a % p; // 如果 k 的二进制最后一位是 1，累乘 a
        }
        a = (LL)a * a % p; // 平方 a
        k >>= 1; // 将 k 右移一位
    }
    return res;
}


int main() {
    int n;
    cin >> n; // 输入 n

    int a = n * 2, b = n; // 设置 a = 2n，b = n
    int res = 1;

    // 计算 \(\binom{2n}{n} \mod mod\) 的分子部分，乘积从 2n 到 n+1
    for (int i = a; i > a - b; -- i) { 
        res = (LL)res * i % mod;
    }

    // 计算分母部分 n! 的逆元，并乘以结果，使用快速幂求逆元
    for (int i = 1; i <= b; ++ i) { 
        res = (LL)res * qmi(i, mod - 2, mod) % mod;
    }
    
    // 计算 n + 1 的逆元，乘到结果上
    res = (LL)res * qmi(n + 1, mod - 2, mod) % mod;

    // 输出最终结果
    cout << res << endl;

    return 0;
}
