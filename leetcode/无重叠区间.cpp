/*
    思路： 贪心，时间Onlogn，空间Ologn
    1. 按右端点从小到大排序
    2. 每次只需要判断该区间和上一个区间是否重合
    3. 如果重合，这个区间就要舍去，否则就留着
*/

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](vector<int>& a, vector<int>& b){
            return a[1] < b[1];
        });
        int& r = intervals[0][1];   // 只需要记录当前区间的右端点
        int res = 1;    // 初始区间为1
        int n = intervals.size();
        for (int i = 1; i < n; ++ i) {
            if (intervals[i][0] >= r) {     // 如果该区间的左端点比之前区间的右端点大，说明不重合
                r = intervals[i][1];    // 更新新区间的右端点
                ++ res; // 该区间可以留用
            }
        }
        return n - res; // 返回被删去的区间数量
    }
};