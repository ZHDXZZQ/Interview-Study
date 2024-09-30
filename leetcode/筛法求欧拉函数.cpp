/*
    思路：计算小于等于 n 的所有正整数的欧拉函数（Euler's Totient Function）并返回它们的和。使用了筛法的思想来有效计算欧拉函数值。
    时间Onloglogn，空间On
*/
#include <iostream>

using namespace std;

typedef long long LL; // 定义 LL 为 long long 的别名，以便处理大数

const int N = 1000010; // 定义常量 N，表示数组的大小

int primes[N], cnt; // primes 数组用于存储素数，cnt 记录素数的数量
int euler[N]; // euler 数组用于存储每个数的欧拉函数值
bool st[N]; // st 数组用于标记合数（false 表示是素数，true 表示是合数）

// 计算小于等于 n 的所有正整数的欧拉函数值
void get_eulers(int n) {
    euler[1] = 1; // 欧拉函数 φ(1) = 1
    for (int i = 2; i <= n; i++) { // 遍历 2 到 n 的每个数
        if (!st[i]) { // 如果 i 是素数
            primes[cnt++] = i; // 存储素数到 primes 数组
            euler[i] = i - 1; // φ(p) = p - 1
        }
        for (int j = 0; primes[j] <= n / i; ++j) { // 遍历所有已知的素数
            int t = primes[j] * i; // 计算合数 t = primes[j] * i
            st[t] = true; // 标记 t 为合数
            if (i % primes[j] == 0) { // 如果 i 是 primes[j] 的倍数
                euler[t] = euler[i] * primes[j]; // 更新 euler[t]
                break; // 退出循环
            }
            euler[t] = euler[i] * (primes[j] - 1); // 计算 euler[t]
        }
    }
}

int main() {
    int n;
    cin >> n; // 输入 n

    get_eulers(n); // 计算小于等于 n 的欧拉函数值

    LL res = 0; // 初始化结果为 0
    for (int i = 1; i <= n; i++) { // 遍历 1 到 n 的每个数
        res += euler[i]; // 累加欧拉函数值
    }

    cout << res << endl; // 输出结果

    return 0; // 返回 0
}
