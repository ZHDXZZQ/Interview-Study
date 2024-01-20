// 思路： 一次遍历，时间On，空间O1
// 1. 遍历整个数组，记录区间的左端点。
// 2. 如果遍历到了最后一个位置，则直接给定右端点进入判断
// 3. 否则判断是否是连续的，如果下一个数字断开了，则确定右端点进入判断，否则继续遍历
// 4. 判断左端点和右端点是否是同一个，用于确定输出的格式
// 5. 该区间插入结果中后，确定新的左端点，重复上述步骤

class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        if(nums.empty()) return {};
        vector<string> res;
        int start = nums[0], end;       //start用于记录当前区间的左端点，end用于记录右端点
        for(int i = 0; i < nums.size(); ++ i) {
            if(i == nums.size() - 1 || (i < nums.size() - 1 && nums[i] + 1 != nums[i + 1])) {   //如果i是数组中最后一个元素，或者不满足连续递增
                end = nums[i];      //确定右端点
                if(start == end) {  //如果左右端点一样，则只输出单个数字
                    res.push_back(to_string(nums[i]));
                } else {        //否则输出x->y
                    res.push_back(to_string(start) + "->" + to_string(end));
                }
                if(i < nums.size() - 1) start = nums[i + 1];    //如果i不到结尾，则确定下一个区间的左端点
            }
        }
        return res;
    }
};