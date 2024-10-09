/*
    思路： 使用分解质因数的方法来计算组合数，并通过大数相乘处理超出普通整型范围的数。
    时间Ond，空间On+d
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 5010; // 最大计算的数值范围

int primes[N], cnt; // primes 数组存储质数，cnt 为质数的个数
int sum[N]; // sum 数组用于记录每个质数的指数和
bool st[N]; // st 数组标记非质数

// 使用线性筛法获取小于等于 n 的所有质数
void get_primes(int n) {
    // 遍历 2 到 n 的每个数
    for (int i = 2; i <= n; ++ i) {
        // 如果 i 是质数，则存入 primes 数组
        if (!st[i]) {
            primes[cnt ++] = i;
        }
        // 枚举所有质数 primes[j]，标记合数
        for (int j = 0; primes[j] <= n / i; ++ j) {
            st[primes[j] * i] = true; // 标记 i * primes[j] 为合数
            // 如果 i 是 primes[j] 的倍数，停止标记
            if (i % primes[j] == 0) {
                break;
            }
        }
    }
}

// 计算 n! 中质数 p 的次数，即计算 n! 中 p 的幂次
int get(int n, int p) {
    int res = 0;
    // 不断除以 p，计算每一轮可以被 p 整除的数量
    while (n) {
        res += n / p;
        n /= p;
    }
    return res;
}

// 高精度乘法：计算大整数 a 乘以普通整数 b，返回结果
vector<int> mul(vector<int> a, int b) {
    vector<int> c; // 存储相乘后的结果
    int t = 0; // t 为进位
    // 从低位开始逐位相乘
    for (int i = 0; i < a.size(); ++ i) {
        t += a[i] * b; // 当前位乘以 b 加上进位
        c.push_back(t % 10); // 保存结果的当前位
        t /= 10; // 计算新的进位
    }
    // 如果还有进位，将其继续处理
    while (t) {
        c.push_back(t % 10);
        t /= 10;
    }
    return c;
}

int main() {
    int a, b;
    cin >> a >> b; // 输入 a 和 b

    // 获取 a 以内的所有质数
    get_primes(a);

    // 计算组合数 C(a, b) 的质因数分解
    for (int i = 0; i < cnt; ++ i) {
        int p = primes[i]; // 当前质数
        // 计算质数 p 在 a! / (b!(a-b)!) 中的幂次
        sum[i] = get(a, p) - get(a - b, p) - get(b, p);
    }

    vector<int> res; // 用于存储高精度的乘法结果
    res.push_back(1); // 初始结果为 1

    // 将质因数按其幂次乘入结果
    for (int i = 0; i < cnt; ++ i) {
        for (int j = 0; j < sum[i]; ++ j) { // 将质数 p 乘入其幂次
            res = mul(res, primes[i]);
        }
    }

    // 输出结果，从高位到低位打印
    for (int i = res.size() - 1; i >= 0; -- i) {
        printf("%d", res[i]);
    }
    puts(""); // 输出换行符

    return 0;
}
