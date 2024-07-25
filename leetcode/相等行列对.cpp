/*
    思路： 哈希表，时间On²，空间On²，注意umap不能用vector作为key，但是map可以
*/

class Solution {
public:
    int equalPairs(vector<vector<int>>& grid) {
        map<vector<int>, int> umap;
        int res = 0;
        int n = grid.size();
        for (int i = 0; i < n; ++ i) {  // 存储所有行
            ++ umap[grid[i]];
        }
        for (int j = 0; j < n; ++ j) {
            vector<int> tmp;
            for (int i = 0; i < n; ++ i) {  // 构造每个列
                tmp.push_back(grid[i][j]);
            }
            res += umap[tmp];   // 将和该列一样的行的数量加入结果中
        }
        return res;
    }
};