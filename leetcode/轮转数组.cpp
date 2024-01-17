// 思路： 求逆，时间On，空间O1
// 1. 前k个求逆，后面的求逆，再整体求逆
// 2. 思路类似于线性代数求逆矩阵的思想

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        k %= nums.size();
        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin() + k);  //第二个参数是开区间
        reverse(nums.begin() + k, nums.end());
    }
};