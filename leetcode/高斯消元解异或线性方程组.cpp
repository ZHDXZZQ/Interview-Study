/*
    思路： 高斯消元，时间On^3，空间On^2
    二进制高斯消元法，用于解决线性方程组的解。与标准高斯消元不同，二进制高斯消元在二进制域上操作，且所有的计算使用按位异或（XOR）来代替加减运算。
*/

#include <iostream>
#include <algorithm>

using namespace std;

const int N = 110;  // 最大矩阵规模

int n;              // 矩阵的阶数（未知数的个数）
int a[N][N];        // 增广矩阵，a[i][n] 存放方程的常数项

// 二进制高斯消元法
int gauss() {
    int c, r;  // c: 当前消元列, r: 当前处理的行
    for (c = 0, r = 0; c < n; ++c) {  // 遍历每一列
        int t = r;
        // 找到当前列中非零的行
        for (int i = r; i < n; ++i) {
            if (a[i][c]) {  // 如果当前行的该列元素非0
                t = i;
            }
        }

        // 如果当前列全为0，跳过该列
        if (!a[t][c]) { 
            continue; 
        }

        // 将第 t 行交换到第 r 行
        for (int i = c; i <= n; ++i) {
            swap(a[r][i], a[t][i]);
        }

        // 将当前列下面所有行该列元素消为0
        for (int i = r + 1; i < n; ++i) {
            if (a[i][c]) {  // 如果当前行该列非0
                for (int j = n; j >= c; --j) {
                    a[i][j] ^= a[r][j];  // 使用异或操作进行消元
                }
            }
        }

        ++r;  // 处理下一行
    }

    // 检查是否有无解情况
    if (r < n) {  // 还未处理完所有行时，可能有无解的情况
        for (int i = r; i < n; ++i) {
            if (a[i][n]) {  // 常数项不为0，说明无解
                return 2;   // 无解
            }
        }
        return 1;  // 有无穷多组解
    }

    // 回代求解
    for (int i = n - 1; i >= 0; --i) {
        for (int j = i + 1; j < n; ++j) {
            a[i][n] ^= a[i][j] * a[j][n];  // 根据已经计算的结果进行回代
        }
    }

    return 0;  // 有唯一解
}

int main() {
    // 输入方程组的阶数 n 和增广矩阵
    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n + 1; ++j) {
            cin >> a[i][j];  // 读取增广矩阵的系数和常数项
        }
    }

    // 调用高斯消元函数并根据返回值判断解的情况
    int t = gauss();
    
    if (t == 0) {  // 有唯一解
        for (int i = 0; i < n; ++i) {
            cout << a[i][n] << endl;  // 输出每个变量的解
        }
    } else if (t == 1) {  // 有无穷多解
        puts("Multiple sets of solutions");
    } else {  // 无解
        puts("No solution");
    }

    return 0;
}
