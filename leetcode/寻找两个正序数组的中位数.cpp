// 思路： 递归/二分，但是这两种都不太好想，我们取巧直接sort，时间Onlogn，空间On
// 有兴趣的同学可以学习一下前面说的两种比较困难的解法

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        for (auto& num : nums2) {
            nums1.emplace_back(num);
        }
        sort(nums1.begin(), nums1.end());
        if (nums1.size() % 2 == 1) {
            return nums1[nums1.size() / 2];
        }
        return (nums1[nums1.size() / 2] + nums1[nums1.size() / 2 - 1]) / 2.0;
    }
};