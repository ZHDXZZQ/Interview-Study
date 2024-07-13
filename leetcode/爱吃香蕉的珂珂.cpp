/*
    思路： 二分，时间Onlogn，空间O1
    1. 每次二分找到一个速度，去计算是否能在规定时间内吃完
    2. 如果耗时更短，说明速度过快，需要降低速度
    3. 如果吃不完，说明速度更慢，需要提高速度，以此二分
*/

class Solution {
public:
    int get_time(vector<int>& nums, int& speed) {   // 记录当前速度下，吃香蕉的耗时
        int res = 0;
        for (auto& bananas : nums) {
            res += (bananas + speed - 1) / speed;   // 上取整方法，这里也可以利用余数计算
        }
        return res;
    }

    int minEatingSpeed(vector<int>& piles, int h) {
        int l = 1, r = 1e9;
        while (l < r) {
            int speed = l + r >> 1; // 速度取中值
            if (get_time(piles, speed) <= h) {  // 如果当前速度能吃完
                r = speed;  // 那么让速度变慢一些，看看能不能以更慢的速度吃完
            } else {    // 否则的话，速度太慢
                l = speed + 1;  // 提高速度吃
            }
        }
        return r;
    }
};