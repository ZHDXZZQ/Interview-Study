/*
    思路： 中国剩余定理，时间O(n * log(m))，其中 n 是同余方程的数量，m 是所有模数的大小。空间Ologm
    给定一组模数和余数，求解符合所有同余方程的最小非负整数解。
*/

#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

// 扩展欧几里得算法，用于求解 ax + by = gcd(a, b) 的一组解
LL exgcd(LL a, LL b, LL &x, LL &y) {
    if (!b) {  // 基础情况，当 b == 0 时，返回 gcd(a, b) = a，并且 x = 1, y = 0
        x = 1, y = 0;
        return a;
    }

    // 递归调用扩展欧几里得算法，返回 gcd(a, b)
    LL d = exgcd(b, a % b, y, x);
    // 更新 x 和 y，使得 a * x + b * y = gcd(a, b) 成立
    y -= a / b * x;
    return d;
}

int main() {
    int n;
    cin >> n;  // 读取同余方程的个数

    // 读取第一个同余方程 m1 和 a1
    LL x = 0, m1, a1;
    cin >> m1 >> a1;

    // 处理后续的 n - 1 个同余方程
    for (int i = 0; i < n - 1; ++ i) {
        LL m2, a2;
        cin >> m2 >> a2;  // 读取新的模数 m2 和余数 a2
        
        LL k1, k2;  // 存储扩展欧几里得算法的结果
        LL d = exgcd(m1, m2, k1, k2);  // 计算 m1 和 m2 的最大公约数 gcd(m1, m2)
        
        // 如果 a2 - a1 不是 gcd(m1, m2) 的倍数，则无解
        if ((a2 - a1) % d) {
            x = -1;
            break;
        }

        // 求解 k1，使得 k1 * m1 + a1 ≡ a2 (mod m2)
        k1 *= (a2 - a1) / d;  // k1 * m1 = (a2 - a1) / gcd(m1, m2)
        k1 = (k1 % (m2/d) + m2/d) % (m2/d);  // 保证 k1 为正数

        // 计算当前方程组的解
        x = k1 * m1 + a1;

        // 更新模数和余数，用于下一轮迭代
        LL m = abs(m1 / d * m2);  // 更新模数为 lcm(m1, m2)
        a1 = k1 * m1 + a1;  // 更新余数
        m1 = m;  // 更新模数
    }

    // 如果有解，计算 x 的最小非负解
    if (x != -1) {
        x = (a1 % m1 + m1) % m1;
    }

    cout << x << endl;  // 输出结果

    return 0;
}
