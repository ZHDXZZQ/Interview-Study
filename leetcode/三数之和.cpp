// 思路： 排序 + 双指针，时间On²，空间Ologn，排序用空间
// 1. 三个指针依次找结果，要注意过滤掉可能重复的情况

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());     //首先排序，时间Onlogn，空间Ologn
        int n = nums.size();
        vector<vector<int>> res;    
        for(int i = 0; i < n; ++ i) {                           //i指向第一个数
            if(i > 0 && nums[i - 1] == nums[i]) continue;       //找第一个数，如果跟前一个一样，则过滤掉重复情况
            for(int j = i + 1, k = n - 1; j < k; ++ j) {        //j指向第二个数，k指向第三个数，每次确定前两个数然后移动k
                if(j > i + 1 && nums[j - 1] == nums[j]) continue;   //找第二个数，如果跟前一个一样，则过滤掉重复情况
                while(j < k - 1 && nums[i] + nums[j] + nums[k - 1] >= 0) -- k;  //移动k，直到移动到三者之和小于0之前停止
                //此时的三者之和是大于等于0的，再往前移动则小于0。因为按序排序，所以当j往后移时，k可以保证后面的位置不需要再考虑
                if(nums[i] + nums[j] + nums[k] == 0) res.push_back({nums[i], nums[j], nums[k]});    //如果此时等于0，则插入答案
            }
        }
        return res;
    }
};