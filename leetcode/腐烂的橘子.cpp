/*
    思路： bfs，时间Omn，空间Omn
    1. 先把所有腐烂的橘子放入队列
    2. 每一分钟，将其四周未腐烂的句子腐烂掉并插入队列
    3. 重复上述循环直到扩散到全部能传播的句子
*/

class Solution {
public:
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0 ,0, 1, -1};
    using PII = pair<int, int>;
    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        queue<PII> q;
        int res = -1;
        for (int i = 0; i < m; ++ i) {  // 初始将所有腐烂的橘子记录
            for (int j = 0; j < n; ++ j) {
                if (grid[i][j] == 2) {
                    q.push({i, j});
                }
            }
        }
        while (q.size()) {  // 只要队列不空，说明还有马上腐烂的橘子未记录
            int cnt = q.size();
            while (cnt --) {    // 记录该分钟腐烂的橘子
                auto pii = q.front();
                q.pop();
                int& i = pii.first;
                int& j = pii.second;
                for (int k = 0; k < 4; ++ k) {  // 并将其向四周传播
                    int x = i + dx[k];
                    int y = j + dy[k];
                    if (x >= 0 && x < m && y >= 0 && y < n && grid[x][y] == 1) {    // 将未腐烂的橘子存入
                        grid[x][y] = 2;
                        q.push({x, y});
                    }
                }
            }
            ++ res; // 时间+1
        }
        for(int i = 0; i < m; i ++) {
            for(int j = 0; j < n; j ++) {
                if(grid[i][j] == 1) return -1;   //如果还有1，表明还有橘子未腐烂，且无法被污染，失败
            }
        }
        if (res == -1) {    // 说明根本就没有腐烂的橘子
            return 0;
        }
        return res;
    }
};