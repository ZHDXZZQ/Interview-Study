/*
    思路： 动态规划，时间Omn，空间O1
    1. 和礼物的最大价值是一道题，直接初始化左边和上边，然后计算即可
    2. 每次只需要从左上往右或往下找，保证自己的上面和左边是当前路径的最大值即可
*/

class Solution {
public:
    int jewelleryValue(vector<vector<int>>& frame) {
        int m = frame.size();
        int n = frame[0].size();
        for (int i = 1; i < m; ++ i) {      // 初始化第一列，每个位置都是最大价值
            frame[i][0] += frame[i - 1][0];
        }
        for (int j = 1; j < n; ++ j) {
            frame[0][j] += frame[0][j - 1]; // 初始化第一行
        }
        for (int i = 1; i < m; ++ i) {  // 从第二行第二列开始，按序走到最后一个格子，每次取max
            for (int j = 1; j < n; ++ j) {
                frame[i][j] += max(frame[i - 1][j], frame[i][j - 1]);   // 选两条路径的最大值再加上当前格子的值
            }
        }
        return frame[m - 1][n - 1];
    }
};