/*
    思路： 记录前缀和，模板题，时间On，空间On
    1. 利用一个数组记录当前位置之前的所有数的和
    2. 查询的区间只需要右端的前缀和减去左端的前缀和就是当前区间的数字和
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> nums(n + 1, 0); // 存储前缀和，0号位置置0，方便计算
    for (int i = 0; i < n; ++ i) {
        int num;    // 输入n个数
        cin >> num;
        nums[i + 1] = num + nums[i];    // 每个位置等于这个数+前一个位置的数，即前缀和，所有前面的数字的和
    }
    while (m --) {  // 输入m组查询
        int l, r;
        cin >> l >> r;  // 输入两个端点
        -- l;   // 左端点要-1，就符合要求
        int res = nums[r] - nums[l];    // 记录结果为两个前缀和相减
        cout << res << endl;
    }
    return 0;
}