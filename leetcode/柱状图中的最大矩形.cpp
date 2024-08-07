/*
    思路： 单调栈，时间On，空间On
    1. 对于每个柱子，记录左边第一个小于它高度的柱子的下标，以及右边第一个小于它高度的柱子的下标
    2. 利用单调栈记录，对于最矮的柱子，那么其两边的下标应该对应n和-1
    3. 然后遍历每个柱子，每次计算以该柱子为最大高度的矩形的最大面积（即两边的第一个低于其高度的柱子之间），求最大值
*/

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        stack<int> rec;  //单调递增栈，用来找第一个小于其高度的柱子，往前找如果碰到更低的，那前面的更低，就不用管了
        vector<int> left(n);  //这两个vector用于记录第一个小于当前柱子高度的左边的柱子和右边的柱子
        vector<int> right(n);  //这里记得要设置vector的大小，也可以用数组
        
        for(int i = 0; i < n; i ++) {  //从左往右记录每个柱子的左边第一个小于其高度的柱子的下标
            while(rec.size() && heights[rec.top()] >= heights[i]) { // 如果当前柱子更低，则前面的没用了
                rec.pop();
            }
            if(rec.empty()) {   // 如果当前柱子就是最矮的
                left[i] = -1;   // 左边没有更矮柱子
            } else {
                left[i] = rec.top();    // 左边第一个更矮的柱子
            }
            rec.push(i);    // 把当前柱子插入
        }
        rec = stack<int>();  //清空栈，不能用clear
        for(int i = n - 1; i >= 0; i --) {  //从右往左记录每个柱子的右边第一个小于其高度的柱子的下标，逻辑同上
            while(rec.size() && heights[rec.top()] >= heights[i]) {
                rec.pop();
            }
            if(rec.empty()) {
                right[i] = n;   // 右边没有更矮柱子
            } else {
                right[i] = rec.top();
            }
            rec.push(i);
        }
        int res = 0;
        for(int i = 0; i < n; i ++) {  //每次更新结果，求以该柱子为最大高度的面积
            int curarea = heights[i] * (right[i] - left[i] - 1);
            res = max(res, curarea);
        }
        return res;
    }
};