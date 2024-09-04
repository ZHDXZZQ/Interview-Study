/*
    思路： 记忆化搜索递归，其实就是dfs，时间Omn，空间Omn
    1. 对于每个节点记录其作为起点能走的步，递归计算
    2. 遍历四周，如果某个方向能走，就递归计算，如果已经有结果，则直接在该结果上+1，取各个方向的最大值
*/

#include <iostream>
#include <vector>

using namespace std;

const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};
int res = 0;
int m, n;

int dfs(vector<vector<int>>& nums, int x, int y, vector<vector<int>>& dp) {
    if (dp[x][y] != -1) {// 如果这个为止已经计算过，返回这个节点为起点能走的最大值即可
        return dp[x][y];
    }
    dp[x][y] = 1;   // 否则的话初始为1，表示至少能走这个节点
    for (int k = 0; k < 4; ++ k) {  // 向4个方向尝试
        int i = x + dx[k];
        int j = y + dy[k];
        if (i >= 0 && j >= 0 && i < m && j < n && nums[i][j] < nums[x][y]) {    // 满足要求的情况下
            if (dp[i][j] == -1) {   // 如果目标节点没被计算过，要dfs计算一下
                dp[x][y] = max(dp[x][y], dfs(nums, i, j, dp) + 1);
            } else {    // 如果已经计算过，直接使用
                dp[x][y] = max(dp[x][y], dp[i][j] + 1);
            }
        }
    }
    res = max(dp[x][y], res);   // 记录最大值
    return dp[x][y];    // 返回当前位置的结果用于递归
}

int main() {
    cin >> m >> n;
    vector<vector<int>> nums(m, vector<int>(n));    // 初始化图
    vector<vector<int>> dp(m, vector<int>(n, -1));  // 初始化每个节点为起点能走的最远距离
    for (int i = 0; i < m; ++ i) {
        for (int j = 0; j < n; ++ j) {
            cin >> nums[i][j];
        }
    }
    for (int i = 0; i < m; ++ i) {
        for (int j = 0; j < n; ++ j) {
            if (dp[i][j] == -1) {   // 如果没有计算过，计算以下
                dfs(nums, i, j, dp);
            }
        }
    }
    cout << res << endl;
    return 0;
}