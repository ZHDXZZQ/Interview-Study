/*
    思路： dfs回溯，时间Omn4^l，空间Ol，m行n列，目标串长度为l
    1. 对于每个为止，进行dfs，如果该位匹配，则向四个方向dfs，同时将该位修改，返回时回溯
*/

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param matrix char字符型vector<vector<>> 
     * @param word string字符串 
     * @return bool布尔型
     */

    int m, n;
    const int dx[4] = {0, 0, 1, -1};
    const int dy[4] = {1, -1, 0, 0};

    bool dfs(int pos, int x, int y, vector<vector<char>>& matrix, string& word) {
        if (word[pos] != matrix[x][y]) {    // 如果不相等，错误
            return false;
        }
        if (pos == word.size() - 1) {   // 如果相等，且到达了最后一个位置，正确
            return true;
        }
        char temp = matrix[x][y];   // 记录用于回溯
        matrix[x][y] = '.';
        for (int k = 0; k < 4; ++ k) {  // 向四个方向遍历
            int i = x + dx[k];
            int j = y + dy[k];
            if (i >= 0 && j >= 0 && i < m && j < n) {   // 如果下一个位置合法
                bool res = dfs(pos + 1, i, j, matrix, word);    // 则进行dfs
                if (res) { return true; }   // 如果有一条路走通，则整体走通
            }
        }
        matrix[x][y] = temp;    // 回溯
        return false;   // 没有能走通的，返回错误
    }

    bool hasPath(vector<vector<char>>& matrix, string word) {
        // write code here
        m = matrix.size();
        n = matrix[0].size();
        for (int i = 0; i < m; ++ i) {
            for (int j = 0; j < n; ++ j) {
                bool res = dfs(0, i, j, matrix, word);
                if (res) { return true; }
            }
        }
        return false;
    }
};