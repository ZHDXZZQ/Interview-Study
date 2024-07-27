/*
    思路： 分组，每个组内只能拿1个，本质是01背包问题，时间Onms，空间On。
*/

#include <iostream>
#include <algorithm>

using namespace std;

const int N = 110;

int n, m;
int v[N][N], w[N][N], s[N];
int f[N];

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++ i) { // 第i个物品组
        cin >> s[i];
        for (int j = 0; j < s[i]; ++ j) {   // 存储第i个物品组的每个物品
            cin >> v[i][j] >> w[i][j];
        }
    }
    for (int i = 1; i <= n; ++ i) { // 取第i个组
        for (int j = m; j >= 0; -- j) { // 体积还有
            for (int k = 0; k < s[i]; ++ k) {   // 遍历组内每个物品
                if (v[i][k] <= j) { // 如果组内该物品小于当前体积
                    f[j] = max(f[j], f[j - v[i][k]] + w[i][k]); // 判断加入当前物品与否的最大值，本质是01背包问题
                }
            }
        }
    }
    cout << f[m] << endl;
    return 0;
}