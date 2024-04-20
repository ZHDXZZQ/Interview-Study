// 思路： 二分，时间Ologn，空间O1
// 1. 有序数组且要求时间Ologn，基本要用二分，找目标值的首尾位置，可以理解为先找到头，再找到尾
// 2. 可以利用目标值-0.5找到头，利用目标值+0.5找到尾，过程如下

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int n = nums.size();
        if (n == 0) return {-1, -1};    //没有数字，返回-1和-1
        int l = 0, r = n - 1;
        double target_1 = target - 0.5; //找头
        while (l < r) {
            int mid = (l + r) / 2;
            if (nums[mid] >= target_1) {    //如果找到的值大或等于，则更小的肯定在左边，也可能在当前位置
                r = mid;
            } else {
                l = mid + 1;    //否则的话一定在右边
            }
        }
        vector<int> res;
        if (nums[r] != target) {    //如果没有找到目标值，直接返回两个-1
            return {-1, -1};
        }
        res.push_back(r);       //否则的话头的位置找到
        l = 0, r = n - 1;
        double target_2 = target + 0.5; //找尾
        while (l < r) {
            int mid = (l + r + 1) / 2;  //因为l = mid，因此这里一定要+1
            if (nums[mid] >= target_2) {    //如果中间值比目标值大于等于
                r = mid - 1;            //这个尾巴一定在左边
            } else {
                l = mid;        //否则在右边，也可能是当前位置
            }
        }
        res.push_back(r);       //插入尾巴位置，只要有头就一定有尾，出现一次就首尾相等
        return res;
    }
};