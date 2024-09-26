/*
    思路： 数位DP，时间Omlgb，空间Olgb
    抄的，以后有时间再研究
*/
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 10; // 定义常量 N 为 10，表示数字范围 0-9

/*
    函数功能：从向量 num 中提取从下标 r 到 l 的数字并返回其组合成的整数
*/
int get(vector<int> num, int l, int r) {
    int res = 0; // 结果变量
    // 从 l 向 r 遍历，组合数字
    for (int i = l; i >= r; -- i) {
        res = res * 10 + num[i];
    }
    return res; // 返回组合的整数
}

/*
    函数功能：计算 10 的 x 次方
*/
int power10(int x) {
    int res = 1; // 初始化结果为 1
    // 计算 10 的 x 次方
    while (x--) {
        res *= 10;
    }
    return res; // 返回结果
}

/*
    函数功能：计算数字 n 中数字 x 出现的次数
*/
int count(int n, int x) {
    if (!n) { return 0; } // 如果 n 为 0，返回 0

    vector<int> num; // 存储 n 的每一位数字
    // 将 n 的每一位数字存入 num 向量
    while (n) {
        num.push_back(n % 10); // 取最低位
        n /= 10; // 除以 10，继续提取下一位
    }
    n = num.size(); // 获取数字的位数

    int res = 0; // 结果变量
    // 从最高位开始遍历每一位
    for (int i = n - 1 - !x; i >= 0; -- i) {
        // 计算高位的贡献
        if (i < n - 1) {
            res += get(num, n - 1, i + 1) * power10(i); // 获取高位数字并计算贡献
            if (!x)  {
                res -= power10(i); // 如果 x 为 0，减去 10 的 i 次方（避免重复计算）
            }
        }

        // 如果当前位等于 x，增加对应的计数
        if (num[i] == x)  {
            res += get(num, i - 1, 0) + 1; // 加上低位的组合数 + 1
        } else if (num[i] > x) {        // 如果当前位大于 x，增加当前位的 10^i 贡献
            res += power10(i); // 当前位大于 x，所有更高的组合都有效
        }
    }

    return res; // 返回 x 在 n 内出现的次数
}

int main() {
    int a, b; // 定义输入变量
    // 循环读取 a 和 b，直到 a 为 0
    while (cin >> a >> b, a) {
        if (a > b) {
            swap(a, b); // 确保 a <= b
        }

        // 对于每个数字 i，计算在范围 [a, b] 内出现的次数
        for (int i = 0; i <= 9; ++ i) {
            cout << count(b, i) - count(a - 1, i) << ' '; // 输出每个数字的出现次数
        }
        cout << endl; // 换行
    }

    return 0; // 程序结束
}
