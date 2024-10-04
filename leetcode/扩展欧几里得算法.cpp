/*
    思路：扩展欧几里得算法， 时间O(log(min(a, b)))，空间O(log(min(a, b)))
*/
#include <iostream>
#include <algorithm>

using namespace std;

// 扩展欧几里得算法，计算 gcd(a, b) 并求出 x 和 y，使得 a * x + b * y = gcd(a, b)
int exgcd(int a, int b, int &x, int &y) {
    // 递归结束条件，如果 b == 0, gcd(a, 0) = a，此时 x = 1，y = 0
    if (!b) {
        x = 1, y = 0;
        return a;  // 返回 gcd(a, b)
    }
    
    // 递归调用，求 gcd(b, a % b) 并返回对应的 x, y
    int d = exgcd(b, a % b, y, x);  // 递归结束后，y, x 已经求得
    
    // 更新 y 的值，使得当前层级的等式 a * x + b * y = gcd(a, b) 成立
    y -= a / b * x;  // 通过公式推导得来 y = y - (a // b) * x
    return d;  // 返回 gcd(a, b)
}

int main() {
    int n;
    scanf("%d", &n);  // 输入 n 表示有 n 组数据

    while (n --) {
        int a, b;
        scanf("%d%d", &a, &b);  // 输入 a 和 b

        int x, y;
        exgcd(a, b, x, y);  // 调用扩展欧几里得算法，计算 x 和 y
        printf("%d %d\n", x, y);  // 输出 x 和 y 的值
    }

    return 0;
}
