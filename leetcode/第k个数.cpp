/*
    思路：快速选择， 时间O2n，即On，空间O1
    1. 找到分界点x，可以是左端点，右端点，或中间点，即哨兵
    2. 左边所有数都<=x，右边所有数都>=x
    3. 递归排序左边或右边
    4. 如果左边所有的数字的数量<k，说明第k个数在右边，这题只需要递归右边，否则递归左边即可，不用全部快排
*/

#include <iostream>

using namespace std;

const int N = 100100;

int n, k;
int q[N];

int quick_sort(int l ,int r, int k) {
    if (l >= r) {
        return q[l];    // q[r]也可以，这里即第k个数了
    }
    int x = q[l + r >> 1];  // 取中间数字作为哨兵
    int i = l - 1, j = r + 1;
    while (i < j) {
        while (q[++ i] < x);    // 从左往右找到第一个大于等于x的数
        while (q[-- j] > x);    // 从右往左找到第一个小于等于x的数
        if (i < j) {            // 如果还在两边，交换
            swap(q[i], q[j]);
        }       // 然后继续找，直到两个碰上，此时左边都小于x，右边都大于x
    }
    int sl = j - l + 1; // 记录左边的数字个数
    if (k <= sl) {  // 如果左边数量多于k，那么k个数就在左边
        return quick_sort(l, j, k);
    }
    return quick_sort(j + 1, r, k - sl);    // 否则第k个数在右边，要把左边的数字去掉
}

int main() {
    cin >> n >> k;
    for (int i = 0; i < n; ++ i) {
        cin >> q[i];
    }
    cout << quick_sort(0, n - 1, k);
    // cout << q[k - 1];    // 直接输出这个也可以
    return 0;
}