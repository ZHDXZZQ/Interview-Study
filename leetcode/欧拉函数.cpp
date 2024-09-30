/*
    思路： 欧拉函数，返回小于等于给定正整数 x 的与 x 互质的正整数的数量。
    时间O根号n，空间O1
*/

#include <iostream>

using namespace std;

// 计算欧拉函数 φ(x)
int phi(int x) {
    int res = x; // 初始化结果为 x
    // 从 2 到 sqrt(x) 遍历所有可能的因子
    for (int i = 2; i <= x / i; i++) {
        if (x % i == 0) { // 如果 i 是 x 的因子
            res = res / i * (i - 1); // 更新 res
            // 去除所有 i 的倍数
            while (x % i == 0) {
                x /= i; // 将 x 除以 i，直到不再能整除
            }
        }
    }
    // 如果 x 仍大于 1，说明 x 是质数
    if (x > 1) {
        res = res / x * (x - 1); // 更新 res
    }
    return res; // 返回 φ(x)
}

int main() {
    int n;
    cin >> n; // 输入测试用例的数量
    while (n--) {
        int x;
        cin >> x; // 输入要计算的 x
        cout << phi(x) << endl; // 输出 φ(x)
    }

    return 0; // 返回 0
}
