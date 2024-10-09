/*
    思路： 容斥原理， 时间Om * 2^m，空间Om
*/
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 20;  // 题目中给定的数 m 最多为 20

int p[N];  // 用于存储 m 个给定的数

int main() {
    int n, m;
    cin >> n >> m;  // 输入 n 和 m

    for (int i = 0; i < m; ++ i) {
        cin >> p[i];  // 输入 m 个数
    }
    int res = 0;
    
    // 使用二进制枚举所有 m 个数的组合
    for (int i = 1; i < 1 << m; ++ i) {
        int t = 1, s = 0;  // t 代表当前组合的乘积，s 代表当前组合中选中的元素个数
        for (int j = 0; j < m; ++ j)
            if (i >> j & 1) {  // 检查第 j 位是否被选中
                if ((LL)t * p[j] > n) {  // 如果乘积超过了 n，跳出循环
                    t = -1;
                    break;
                }
                t *= p[j];  // 计算组合的乘积
                ++ s;  // 记录选中的元素个数
            }

        if (t != -1) {  // 如果 t 没有溢出
            if (s % 2) {
                res += n / t;  // 如果选中的元素个数是奇数，则加上 n / t
            } else {
                res -= n / t;  // 如果选中的元素个数是偶数，则减去 n / t
            }
        }
    }

    cout << res << endl;  // 输出结果

    return 0;
}
