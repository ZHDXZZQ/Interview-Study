// 思路： 原地多维动态规划， 时间Omn，空间O1
// 1. 每个格子用来记录从左上角走到当前格子的和，可以不用额外数组

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        for(int i = 1; i < m; ++ i) {       //对于第一列，只能往下走，每格记录从左上角做到当前格子的和
            grid[i][0] += grid[i - 1][0];
        }
        for(int j = 1; j < n; ++ j) {       //对于第一行，只能往右走，每格记录从左上角做到当前格子的和
            grid[0][j] += grid[0][j - 1];
        }
        for(int i = 1; i < m; ++ i) {       //其他的所有格子，都可以选择从左边的格子或从上边的格子走来
            for(int j = 1; j < n; ++ j) {
                grid[i][j] += min(grid[i - 1][j], grid[i][j - 1]);  //选择从值最小的格子走来，并更新当前格子的值
            }
        }
        return grid[m - 1][n - 1];
    }
};