/*
    思路： 时间Ologn，空间Onlogp
    快速幂算法（modular exponentiation）计算模反元素，并且使用了费马小定理来实现。
    通过不断将指数减半来优化幂运算，从而实现高效计算。对于奇数次幂，将结果乘上当前的底数a；对于偶数次幂，底数自乘后更新指数。
*/

#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

// 快速幂取模函数：计算 (a^b) % p
LL qmi(int a, int b, int p) {
    LL res = 1; // 初始化结果为 1
    while (b) { // 当指数 b 不为 0 时
        if (b & 1) { // 如果 b 是奇数，说明要乘上当前的 a 值
            res = res * a % p; // 更新结果并取模 p
        }
        a = a * (LL)a % p; // a 自乘（平方），并取模 p
        b >>= 1; // b 右移一位（相当于除以 2）
    }
    return res; // 返回结果
}

int main() {
    int n;
    scanf("%d", &n); // 读取测试用例的数量
    while (n --) {
        int a, p;
        scanf("%d%d", &a, &p); // 读取 a 和 p 的值
        if (a % p == 0) { // 如果 a 能整除 p（即 a % p == 0）
            puts("impossible"); // 模 p 逆元不存在，输出 "impossible"
        } else {
            // 使用费马小定理计算 a 的模 p 的逆元，即 a^(p-2) % p
            printf("%lld\n", qmi(a, p - 2, p));
        }
    }

    return 0;
}
