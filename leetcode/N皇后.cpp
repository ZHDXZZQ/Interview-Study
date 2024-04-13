// 思路： 回溯，时间On！，空间On
// 1. 搜索每个位置，只需要考虑当前位置的行、列和斜线上是否有已被占位
// 2. 我们可以按行搜，每行必有一个棋子；每行按列搜，因此只需要考虑其对角线和列上是否有棋子即可
// 3. 第一行搜n个，第二行搜n-1个位置，第三行搜n-2个位置，因此时间On！
// 4. 对于如何存储某一斜线上是否有棋子，可以假设数组是一个坐标系，利用y=x+k和y=-x+k两条直线可以表示所有的斜线。对于斜率为1的直线要考虑截距为负的情况，因此计算时可以统一加一个偏移量

class Solution {
public:
    void dfs(int row) { //回溯
        if (row == size) {  //如果当前行已经超过范围，则把现有答案存入结果中，算作一种解法
            res.push_back(path);
            return;
        }
        for (int i = 0; i < size; ++ i) {   //对于该行，遍历所有的列
            if (col[i] == false && k1[row + i] == false && k2[row - i + size] == false) {   //如果该格子满足条件
                col[i] = k1[row + i] = k2[row - i + size] = true;   //则将该格子插入棋盘
                path[row][i] = 'Q';
                dfs(row + 1);               //进行dfs
                path[row][i] = '.';         //回溯
                col[i] = k1[row + i] = k2[row - i + size] = false;
            }
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        size = n;           //初始化
        col = vector<bool>(n, false);
        k1 = vector<bool>(n * 2, false);
        k2 = vector<bool>(n * 2, false);
        path = vector<string>(n, string(n, '.'));   //初始化当前棋盘
        dfs(0);
        return res;
    }

private:
    int size;
    vector<bool> col;   //记录某列和斜线是否已经有棋子
    vector<bool> k1;
    vector<bool> k2;
    vector<vector<string>> res;
    vector<string> path;
};