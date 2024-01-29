// 思路： 深度优先搜索dfs，时间Omn，空间O1。以后思路简化只讲想法不讲写法，具体代码写法在下面的注释中
// 1. 遍历所有位置，如果碰到陆地，岛屿数量+1，同时一次性把这个陆地以及接壤的陆地全部变为水
// 2. 然后接着遍历其他位置，重复第一步

class Solution {
public:
    int dx[4] = {0, 1, 0, -1};   //方便遍历某个位置的上下左右
    int dy[4] = {1, 0, -1, 0};

    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int res = 0;
        for(int i = 0; i < m; ++ i) {
            for(int j = 0; j < n; ++ j) {   //遍历所有位置
                if(grid[i][j] == '1') {     //如果当前位置是陆地
                    ++ res;         //岛屿数量+1
                    dfs_clear(grid, i, j);  //把该陆地及其接壤陆地全部变为水
                }
            }
        }
        return res;
    }

    void dfs_clear(vector<vector<char>>& grid, int& x, int& y) {
        grid[x][y] = '0';       //将该位置变为水
        for(int k = 0; k < 4; ++ k) {   //遍历其上下左右
            int cur_x = x + dx[k];
            int cur_y = y + dy[k];
            if(cur_x >= 0 && cur_x < grid.size() && cur_y >= 0 && cur_y < grid[0].size() && grid[cur_x][cur_y] == '1') {
                dfs_clear(grid, cur_x, cur_y);  //如果坐标符合范围且为陆地，将其及接壤陆地变为水
            }
        }
    }
};