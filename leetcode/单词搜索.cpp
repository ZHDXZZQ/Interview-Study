// 思路： 回溯剪枝递归， 时间Omn（3^L），空间OL，其中L为word的长度
// 1. 每次判断当前位置是否符合要求，如果符合再向四周判断
// 2. 要注意判断四周时需先把当前位置设置为不可判断，否则可能反向找当前的位置
// 3. 最后记得回溯把当前位置还原

class Solution {
public:
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int m, n;

    bool dfs(int pos, string& word, vector<vector<char>>& board, int x, int y) {
        if(pos == word.size() - 1 && board[x][y] == word[pos]) {    //如果已经抵达字符串的最后一个字符且符合，则当前分支满足要求
            return true;
        }
        if(board[x][y] != word[pos]) {      //如果当前字符和字符串目标字符不同，返回错误
            return false;
        }
        char cur = board[x][y];     //记录当前位置的字符
        board[x][y] = '0';          //将其标记为不可判断
        for(int k = 0; k < 4; ++ k) {   //向四周判断
            int i = x + dx[k];
            int j = y + dy[k];
            if(i < 0 || j < 0 || i >= m || j >= n) continue;    //如果越界则不判断
            if(dfs(pos + 1, word, board, i, j)) return true;    //否则向每个方向判断，只要有一个方向满足要求，则无需继续查找
        }
        board[x][y] = cur;      //回溯，还原当前字符
        return false;           //如果该分支找完四周都没有满足要求的，该分支失败
    }

    bool exist(vector<vector<char>>& board, string word) {
        m = board.size();
        n = board[0].size();
        for(int i = 0; i < m; ++ i) {
            for(int j = 0; j < n; ++ j) {       //从每个结点开始遍历四周
                if(dfs(0, word, board, i, j)) return true;      //只要有一个分支成功，则整体成功
            }
        }
        return false;
    }
};