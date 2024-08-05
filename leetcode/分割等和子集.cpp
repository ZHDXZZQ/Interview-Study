/*
    思路： 01背包，时间On²，空间On
    1. 先计算总和，如果是奇数，那么永远不可能有两个子集相等
    2. 否则是偶数，一半即为每个子集应该的和
    3. 定义dp数组，dp[i]表示数字i能否由某个子集组成
    4. 只需要遍历数组记录哪些数字能被拼接构成即可
    5. 如果目标值的一半可以被组成，那么另一半就也一定可以被组成
*/

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for (auto& x : nums) {  // 计算总和
            sum += x;
        }
        if (sum % 2 == 1) { // 为奇数无需继续
            return false;
        }
        sum /= 2;   // 否则得到一半，即为每个子集的目标和
        vector<bool> dp(sum + 1, false);
        dp[0] = true;   // 初始化0可以被构成
        for (auto& x : nums) {  // 遍历所有数组
            for (int i = sum; i >= x; -- i) {   // 对于每个数，从目标数开始往下遍历
                dp[i] = dp[i] || dp[i - x]; // 如果i-x可以得到，那么i也可以得到
            }
        }
        return dp[sum];
    }
};