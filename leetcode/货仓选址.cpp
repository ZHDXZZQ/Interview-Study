/*
    思路： 绝对值不等式，时间Onlogn，空间On
    1. 可以画图看，对于奇数个点，最中点其他所有点的距离和是最小的
    2. 对于偶数个点，最中间两个点的任意一个点到其他所有点的距离的和是最小的
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; ++ i) {
        cin >> nums[i];
    }
    sort(nums.begin(), nums.end());
    int res = 0;
    int target = nums.size() / 2;   // 目标仓库点
    for (int i = 0; i < n; ++ i) {
        res += abs(nums[i] - nums[target]);
    }
    cout << res;
    return 0;
}