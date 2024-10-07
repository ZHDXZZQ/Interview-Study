/*
    思路： 高斯消元，时间On²，空间On²
    通过逐行操作，将系数矩阵转换为上三角矩阵，然后通过回代求解方程。具体包括消元、行交换、以及判定方程的解是否唯一、无解或有无穷多解。
*/
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

const int N = 110;      // 最大矩阵规模
const double eps = 1e-8; // 浮点数比较时的误差范围

int n;                  // 矩阵的阶数（即方程组中未知数的个数）
double a[N][N];         // 增广矩阵，a[i][n]存放常数项

// 高斯消元算法，返回方程组的解的情况
int gauss() { 
    int c, r;  // c: 当前消元列，r: 当前处理的行
    for (c = 0, r = 0; c < n; ++c) { 
        // 找到当前列绝对值最大的行
        int t = r;
        for (int i = r; i < n; ++i) { 
            if (fabs(a[i][c]) > fabs(a[t][c])) { // 比较绝对值，选最大者
                t = i;
            }
        }

        // 如果最大值接近0，跳过该列
        if (fabs(a[t][c]) < eps) { continue; }

        // 将绝对值最大的行换到当前行
        for (int i = c; i <= n; ++i) {
            swap(a[t][i], a[r][i]);
        }

        // 将当前行首位（即主元）变为1
        for (int i = n; i >= c; --i) {
            a[r][i] /= a[r][c];
        }

        // 将当前列下面所有行的该列元素消为0
        for (int i = r + 1; i < n; ++i) {  
            if (fabs(a[i][c]) > eps) {
                for (int j = n; j >= c; --j) {
                    a[i][j] -= a[r][j] * a[i][c];
                }
            }
        }

        ++r;  // 处理下一行
    }

    // 检查是否有无解的情况
    if (r < n) {  // 如果未能成功处理完所有行
        for (int i = r; i < n; ++i) {
            if (fabs(a[i][n]) > eps) { // 增广矩阵中的常数项不为0，说明无解
                return 2; // 无解
            }
        }
        return 1; // 有无穷多组解
    }

    // 通过回代得到唯一解
    for (int i = n - 1; i >= 0; --i) {
        for (int j = i + 1; j < n; ++j) {
            a[i][n] -= a[i][j] * a[j][n];
        }
    }

    return 0; // 有唯一解
}

int main() {
    // 输入方程组的阶数n和增广矩阵
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n + 1; ++j) {
            scanf("%lf", &a[i][j]);
        }
    }

    // 调用高斯消元法并根据返回值判断解的情况
    int t = gauss();
    if (t == 2) {
        puts("No solution");
    } else if (t == 1) {
        puts("Infinite group solutions");
    } else {
        // 输出唯一解
        for (int i = 0; i < n; i++) {
            printf("%.2lf\n", a[i][n]);
        }
    }

    return 0;
}
