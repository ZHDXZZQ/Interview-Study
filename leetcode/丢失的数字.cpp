// 思路： 和减和，时间On，空间O1
// 1. 先计算1-n的和
// 2. 用这个全部的和减去nums中的所有数
// 3. 最终的结果就是nums中缺少的这个数字

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        long long res = (n * (n + 1)) / 2;  //求和公式
        for (auto& num : nums) {        //依次减去所有数
            res -= num;
        }
        return res;
    }
};