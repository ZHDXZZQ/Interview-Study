/*
    思路： 组合数定理，时间On^2，空间On^2
    C a b = C a-1 b-1 + C a-1 b
    通过这个规律可以利用动态规划提前计算好所有组合数的结果
*/

#include <iostream>

using namespace std;

const int N = 2020;
const int mod = 1e9 + 7;

int C[N][N];

void init() {
    for (int i = 0; i < N; ++ i) {
        for (int j = 0; j <= i; ++ j) {
            if (i == 0 || j == 0) { // 为0时，1种选择
                C[i][j] = 1;
            } else if (i == j) {    // 相同时，1种选择
                C[i][j] = 1;
            } else {
                C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
            }
        }
    }
}

int main() {
    init();
    int n;
    cin >> n;
    while (n --) {
        int a, b;
        cin >> a >> b;
        cout << C[a][b] << endl;;
    }
    return 0;
}