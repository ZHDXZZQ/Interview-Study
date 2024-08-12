/*
    思路： 差分，时间On，空间On
    1. 利用差分数组b来记录结果，原数组a为结果数组b的前缀和
    2. 对于在a的l到c之间的数字+c的操作来说，只需要把差分数组的l部分加上c，r+1部分减去c
    3. 这样的话，l到c之间计算前缀和，就可以令l到c之间的数字都加上c，而r之后的数字计算前缀和，就不会带上c
    4. 差分数组b的前缀和数组即为答案
*/

#include <iostream>
#include <vector>

using namespace std;

void insert(int& l, int& r, int& c, vector<int>& a, vector<int>& b) {
    b[l] += c;
    b[r + 1] -= c;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1, 0);
    vector<int> b(n + 1, 0);
    for (int i = 1; i <= n; ++ i) {
        cin >> a[i];
        insert(i, i, a[i], a, b);   // 初始化差分数组，目标为差分数组的前缀和即为原数组a
    }
    while (m --) {
        int l, r, c;
        cin >> l >> r >> c;
        insert(l, r, c, a, b);  // 继续构造差分数组
    }
    for (int i = 1; i <= n; ++ i) { // 记录结果数组的前缀和，即为答案
        b[i] += b[i - 1];
    }
    for (int i = 1; i <= n; ++ i) {
        cout << b[i] << " ";
    }
    return 0;
}