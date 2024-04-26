// 思路：利用哈希集合，时间On+m，空间Omax（m，n）
// 1. 利用一个不重合的集合记录一个集合中有的值，然后遍历另一个集合判断

class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> set;
        vector<int> res;
        for (auto& num : nums1) {   //将nums1的数值都记录
            set.insert(num);
        }
        for (auto& num : nums2) {   //判断nums2的数值是否在nums1中
            if (set.count(num)) {   //如果在，则存入结果，并将该值从set中删除，防止重复记录
                res.push_back(num);
                set.erase(num);
            }
        }
        return res;
    }
};