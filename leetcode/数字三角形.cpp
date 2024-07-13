/*
    思路： 线性dp，时间On²，空间O1
    1. 只能往左下和右下走，那么当前这个接点的路径一定是从左上或右上走来的
    2. 每次计算一下从上面往下走的最大值计算即可
*/

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> nums(n);
    int num;    // 先插入顶端的数字
    cin >> num;
    nums[0].emplace_back(num);
    for (int i = 1; i < n; ++ i) {
        for (int j = 0; j <= i; ++ j) {
            cin >> num; // 输入下面每一行的每一个数字
            if (j == 0) {   // 如果这个数字是第一列，那么经过它的话只能从右上走来，直接加上
                num += nums[i - 1][j];
            } else if (j == i) {    // 如果是最后一列，只能从左上走来，直接加上
                num += nums[i - 1][j - 1];
            } else {    // 在中间的话，可以从左上或右上走来，记录一下到达上两个点的最大路径，再加上这里
                num += max(nums[i - 1][j - 1], nums[i - 1][j]);
            }
            nums[i].emplace_back(num);  // 当前插入的值为走到这个节点的最大价值
        }
    }
    int res = INT_MIN;
    for (auto& x : nums[n - 1]) {   // 遍历最后一行
        res = max(res, x);  // 找出最大价值
    }
    cout << res;
    return 0;
}