/*
    思路： 贪心，时间Onlogn，空间O1
    1. 先将区间按左端点排序，每次尽可能地将多个区间重合的部分找到
    2. 直到该区间与前面区间重合部分不重合，则开始找后面几个区间重合的部分
    3. 每个多区间重合的部分里面就包含一个点，这个点就是选出的点
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> nums(n, vector<int>(2, 0));
    for (int i = 0; i < n; ++ i) {
        cin >> nums[i][0] >> nums[i][1];    // 输出
    }
    sort(nums.begin(), nums.end()); // 按左端点排序
    int res = 1;    // 初始值为1，因为最后一个重合区间不会被记录，因此提前记录
    int l = nums[0][0], r = nums[0][1]; // 初始化第一个区间，用于寻找前n个区间的重合区间
    for (int i = 1; i < n; ++ i) {
        int& x = nums[i][0];
        int& y = nums[i][1];
        if (x > r) {    // 如果该区间的左端点已经超过当前重合区间的右端点，则该区间及之后不可能和之前的区间都重合
            ++ res; // 因此当前重合区间中有一个点
            l = x;  // 更新下一个区间的开始，找后面的重合区间
            r = y;
        } else {    // 否则该区间可以和前面的区间有重合部分
            l = max(l, x);  // 找最小重合区间，确保其中的点在这n个区间都能找到
            r = min(r, y);
        }
    }
    cout << res << endl;
    return 0;
}