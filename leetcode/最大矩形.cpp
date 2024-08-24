/*
    思路： 单调栈，时间Omn，空间Omn
    1. 利用之前题目的方法，利用单调栈统计每个柱子的左右第一个低于其高度的柱子的位置，这样可以计算基于当前柱子高度的矩形的最大面积
    2. 然后对于这一题的图，针对每一行记录其以该行为底的柱子的高度，把每一行为底的柱状图放入函数中计算面积，求最大值
*/

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        stack<int> rec;     // 单调递增栈，用于记录首个低于该柱子的柱子编号
        vector<int> left(n);   // 第i处的值表示左边第一个小于i柱子高度的柱子下标
        vector<int> right(n);  // 第i处的值表示右边第一个小于i柱子高度的柱子下标

        for (int i = 0; i < n; ++ i) {
            while (rec.size() && heights[rec.top()] >= heights[i]) {    // 找到左边第一个比其低的柱子
                rec.pop();
            }
            if (rec.empty()) {  // 没有更低的，插入-1
                left[i] = -1;
            } else {
                left[i] = rec.top();
            }
            rec.push(i);    // 递增栈，插入当前柱子
        }

        rec = stack<int>(); // 清空栈

        for (int i = n - 1; i >= 0; -- i) { // 从右往左记录
            while (rec.size() && heights[rec.top()] >= heights[i]) {
                rec.pop();
            }
            if (rec.empty()) {
                right[i] = n;
            } else {
                right[i] = rec.top();
            }
            rec.push(i);
        }

        int res = 0;

        for (int i = 0; i < n; ++ i) {
            int cur_area = heights[i] * (right[i] - left[i] - 1);   // 计算以当前柱子高度为基准的，最大矩形的面积
            res = max(res, cur_area);
        }
        
        return res;
    }

    int maximalRectangle(vector<vector<char>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));   // dp[i][j]记录的是以第i行为底，第j列的柱子的高度
        for (int i = m - 1; i >= 0; -- i) {
            for (int j = 0; j < n; ++ j) {
                if (matrix[i][j] == '1') {  // 如果当前格子有东西
                    if (i == m - 1) {   // 如果是顶行，那么这高度就是1
                        dp[i][j] = 1;
                    } else {        // 否则的话，高度就是上一行的高度+1，对于浮空的格子，这一行如果是0那就是0了，因为在上一行计算过了，所以可以扔掉
                        dp[i][j] = dp[i + 1][j] + 1;
                    }
                }
            }
        }
        int res = 0;
        for (int i = m - 1; i >= 0; -- i) {
            res = max(res, largestRectangleArea(dp[i]));    // 将以每行为底的柱状图放入计算当前的最大矩形的面积
        }
        return res;
    }
};