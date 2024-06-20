/*
    思路： 哈希表，时间On，空间On
    1. 直接用两个set来反复判断即可
*/

class Solution {
public:
    vector<vector<int>> findDifference(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> set1, set2;  // 将两个数组的数字都存到set里面
        for (auto& num : nums1) {
            set1.insert(num);
        }
        for (auto& num : nums2) {
            set2.insert(num);
        }
        vector<int> res1, res2; // 存两次比较的结果，这里可以直接用res初始化2个vec在里面即可
        for (auto& num : set1) {
            if (!set2.count(num)) {
                res1.push_back(num);
            }
        }
        for (auto& num : set2) {
            if (!set1.count(num)) {
                res2.push_back(num);
            }
        }
        vector<vector<int>> res;
        res.push_back(move(res1));
        res.push_back(move(res2));
        return res;
    }
};