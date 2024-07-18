/*
    思路： 贪心，时间Onlogn，空间Ologn，排序消耗
    1. 按右端点从小到大排序
    2. 每次只需要判断该区间和上一个区间是否重合
    3. 如果重合，这个区间就要舍去，否则就留着
    贪心方法的证明：贪心解>=最优解，贪心解<=最优解，则贪心解=最优解
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    vector<vector<int>> nums(n, vector<int>(2, 0));
    for (int i = 0; i < n; ++ i) {
        cin >> nums[i][0];
        cin >> nums[i][1];
    }   // 初始化
    sort(nums.begin(), nums.end(), [](vector<int>& a, vector<int>& b) {
        return a[1] < b[1];
    }); // 排序
    int res = 1;    // 最后一个区间不会被判断，直接从1开始计数
    int& r = nums[0][1];    // 初始化r为第一个区间的右端点
    for (int i = 1; i < n; ++ i) {
        int& l = nums[i][0];    // 下一个区间的左端点
        if (l > r) {    // 如果这个区间的左端点大于上一个区间的右端点
            ++ res; // 则这两个区间没有重叠
            r = nums[i][1]; // 由于按右端点从小到大排序，因此后面的直接和当前区间的右端点判断是否重叠，这里采用贪心的思维
        }   // 如果当前区间和上一个区间有重叠，则跳过
    }
    cout << res << endl;
    return 0;
}