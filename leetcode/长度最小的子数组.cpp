// 思路： 双指针模拟滑动窗口，时间On，空间O1
// 1. 设置左右指针，指针间的内容当作一个窗口
// 2. 先是考虑往窗口内加数字，如果窗口内的数字和满足要求了，那么接着加数字一定也满足要求
// 3. 但是求的是最小区间，因此要考虑能否往出拿数字
// 4. 从左边往外拿数字，如果拿出数字后还满足要求，则更新答案并接着拿数字。否则往里加数字
// 5. 注意考虑边界的特殊情况

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int left = 0, right = 0;        //left表示靠左的指针，right表示靠右的指针 
        int res = INT_MAX;              //记录答案，因为取最小值，所以初始设为最大值
        int sum = 0;                    //当前窗口内的和
        int n = nums.size();            //数组大小
        int type = 0;                   //0表示往里加，1表示往外减
        while (right <= n) {            //right要考虑为n的情况，因为left此时还可能要往出减数
            if (type == 0) {
                if(right >= n) break;   //如果right超过数组边界，此时还要加，说明无法再加
                sum += nums[right ++];  //将right所指数字加入窗口中
                if (sum >= target) {    //如果该窗口内的和符合要求
                    res = min(res, right - left);   //更新答案
                    type = 1;           //转而开始往外减
                }
            } else if (type == 1) {     
                sum -= nums[left ++];   //将left所指数减出去
                if (sum >= target) {    //如果此时还是大于目标
                    res = min(res, right - left);   //更新答案
                } else {
                    type = 0;           //否则开始加
                }
            }
        }
        if(res == INT_MAX) return 0;    //如果res没有变，说明没有符合的答案
        return res;
    }
};