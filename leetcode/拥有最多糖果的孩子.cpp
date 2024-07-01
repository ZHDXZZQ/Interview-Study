/*
    思路： 枚举，时间On，空间O1
    1. 首先遍历数组得到最大值
    2. 再次遍历数组，判断每个孩子得到额外糖果的值和最大值的关系
*/

class Solution {
public:
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
        int max_candies = 0;
        for (auto& num : candies) {
            max_candies = max(max_candies, num);
        }
        vector<bool> res;
        for (auto& num : candies) {
            if (num + extraCandies >= max_candies) {    // 如果可以达到最大值
                res.push_back(true);    // 插入true
            } else {
                res.push_back(false);   // 否则插入false
            }
        }
        return res;
    }
};