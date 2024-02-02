// 思路： 集合，时间On，空间On，相当于遍历了三遍数组O3n
// 1. 先遍历一次数组，将所有数存起来
// 2. 再遍历一次数组，查找连续的情况
// 3. 为了避免同一连续序列中的数遍历多次，我们只从连续序列中的最小数开始遍历即可
// 4. 因此如果发现当前数减一存在的话，表明该数不是连续序列的最小数，则跳过不遍历
// 5. 否则从最小数开始依次+1遍历，直到不连续位置，更新答案

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> nums_cp;             //用于存储所有数
        for (const auto num : nums) nums_cp.insert(num);      //把所有数插进去，不能加引用
        int res = 0;                //记录答案最大值
        for (auto& x : nums) {      //遍历每个数
            if(nums_cp.find(x - 1) != nums_cp.end()) continue;  //如果不是连续的最小数则跳过，避免多次遍历
            auto cur = x;           //如果是连续的最小数，从这个数开始往后遍历
            int cnt = 0;            //记录个数
            while(nums_cp.find(cur) != nums_cp.end()) { //如果当前数存在
                ++ cnt;             //则数量+1
                ++ cur;             //当前数指向连续的下一个数
            }
            res = max(res, cnt);
        }
        return res;
    }
};