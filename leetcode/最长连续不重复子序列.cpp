/*
    思路： 双指针，时间On，空间On
    1. 利用哈希表存储当前窗口内每个字符的数量
    2. 每次更新最大数量
    3. 如果某次扩大窗口导致某个字符的数量超过1，左指针缩小窗口，直到把这个字符弹出为止
    4. 重复上述步骤
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {   // 记录所有数字
        cin >> nums[i];
    }
    unordered_map<int, int> num_cnt;    // k表示数字，v表示该数字出现的次数
    int left = 0, right = 0;    // 左右指针，中间就是窗口
    int res = 0;
    while (right < n) { // 如果右窗口没到头
        int num = nums[right];  // 将当前数字入map
        ++ num_cnt[num];
        while (num_cnt[num] > 1) {  // 如果当前数字数量大于1
            -- num_cnt[nums[left ++]];  // 则不断弹出左端数字，直到该数字弹出
        }
        res = max(res, right - left + 1);   // 每次更新最大窗口
        ++ right;
    }
    cout << res << endl;
    return 0;
}