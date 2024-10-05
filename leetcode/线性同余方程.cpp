/*
    思路： 扩展欧几里得算法，时间O(log(min(a, b)))，空间O(log(min(a, m)))
*/

#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;  // 定义 LL 为 long long 类型的简写，用于处理大数运算

// 扩展欧几里得算法，求解 ax + by = gcd(a, b)
// 返回 gcd(a, b)，同时 x 和 y 为方程的一个解
int exgcd(int a, int b, int &x, int &y) {
    if (!b) {  // 当 b 为 0 时，gcd(a, 0) = a，此时 x = 1, y = 0
        x = 1, y = 0;
        return a;
    }
    // 递归调用扩展欧几里得算法
    int d = exgcd(b, a % b, y, x);
    // 更新 y，使得 a * x + b * y = gcd(a, b) 成立
    y -= a / b * x;
    return d;  // 返回 gcd(a, b)
}

int main() {
    int n;  // 读取测试用例数量
    scanf("%d", &n);
    while (n --) {  // 对每一个测试用例进行处理
        int a, b, m;
        scanf("%d%d%d", &a, &b, &m);  // 读取 a, b, m

        int x, y;
        int d = exgcd(a, m, x, y);  // 使用扩展欧几里得算法求解 ax + my = gcd(a, m)
        
        // 如果 b 无法被 gcd(a, m) 整除，则方程 ax ≡ b (mod m) 无解
        if (b % d) {
            puts("impossible");
        } else {
            // 方程有解，解为 (b / d) * x 模 m
            printf("%d\n", (LL)b / d * x % m);  
        }
    }

    return 0;
}
