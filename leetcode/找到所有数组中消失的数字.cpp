/*
    思路： 巧妙思想，时间On，空间O1
    1. 数组中的每个数字都是1~n的范围
    2. 我们可以利用正负标记某个数字是否出现过
    3. 对于1~n的数字，对应的下标时0~n-1
    4. 所以对于每一个数字，我们找到其下标，如果里面的数字是正数，我们将其变为负数，这样标记这个下标对应的值出现过即可
*/

class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        for (auto& num : nums) {
            if (nums[abs(num) - 1] > 0) {   // 有可能已经是负数，所以要取绝对值
                nums[abs(num) - 1] *= -1;   // 如果里面是正数，变为相反数，代表这个下标对应的值出现过了
            }
        }
        vector<int> res;
        for (int i = 0; i < nums.size(); ++ i) {    // 遍历每个数
            if (nums[i] > 0) {  // 如果为正，说明没有出现过
                res.push_back(i + 1);   // 将其对应的值存入结果
            }
        }
        return res;
    }
};