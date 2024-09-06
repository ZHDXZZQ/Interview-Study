/*
    思路： dfs，时间Omn，空间Omn
    经典dfs，看注释
*/

class Solution {
public:
    int th;
    int m, n;
    int res;
    const int dx[4] = {1, -1, 0 ,0};    // 四个方向
    const int dy[4] = {0, 0, 1, -1};
    vector<vector<bool>> used;  // 是否走过

    int calc_sum(int i, int j) {    // 计算两个数字的每位之和
        int sum = 0;
        while (i) {
            sum += (i % 10);
            i /= 10;
        }
        while (j) {
            sum += (j % 10);
            j /= 10;
        }
        return sum;
    }

    void dfs(int x, int y) {    // dfs
        ++ res; // 走到该位置，结果+1
        for (int k = 0; k < 4; ++ k) {  // 向四个方向尝试走
            int i = x + dx[k];
            int j = y + dy[k];
            int sum = calc_sum(i, j);   // 计算和
            if (i >= 0 && j >= 0 && i < m && j < n && sum <= th && used[i][j] == false) {   // 如果没越界且没走过且可以走
                used[i][j] = true;  // 进入该位置
                dfs(i, j);
            }
        }
    }

    int movingCount(int threshold, int rows, int cols) {
        th = threshold;
        m = rows;
        n = cols;
        res = 0;
        used = vector<vector<bool>>(m, vector<bool>(n, false)); // 初始化
        used[0][0] = true;
        dfs(0, 0);
        return res;
    }
};