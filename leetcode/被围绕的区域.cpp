// 思路： 深度优先遍历，时间Omn，空间Omn栈空间
// 1. 什么情况下O是被包围的？什么情况下O是应该不变的呢？
// 2. 思考后发现O被包围的话，四周一定都是X。而不许变化的O，一定不被包围，也就是说他们相连的O至少有一个在边界上
// 3. 所以如果我们遍历每个O，就要考虑前面的情况，这会导致死循环。换一个思路，只要从边界的O往内遍历所有连接的O即可
// 4. 从边界的O往里遍历不到的O就是被包围的应该变成X的O
// 5. 因此，我们从四个边界的O往里做标记，最后将标记的位置改成O，其余的O改成x即可

class Solution {
public:
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0 , 0, 1, -1};

    void change(vector<vector<char>>& board, int i, int j) {
        board[i][j] = 'V';          //当前位置是从边界而来的，标记成V，这些是最后为O的位置
        for(int k = 0; k < 4; ++ k) {       //遍历当前的四个方向
            int x = i + dx[k];
            int y = j + dy[k];
            if(x < 0 || y < 0 || x >= board.size() || y >= board[0].size()) {
                continue;           //如果越界了或者为V或者为X都不管
            } else if(board[x][y] == 'O') {
                change(board, x, y);    //如果为O，则继续遍历
            }
        }
    }

    void solve(vector<vector<char>>& board) {
        int m = board.size();
        int n = board[0].size();
        for(int i = 0; i < m; ++ i) {   //遍历每一行的首尾，随意为O的位置深度遍历
            if(board[i][0] == 'O') {
                change(board, i, 0);
            }
            if(board[i][n - 1] == 'O') {
                change(board, i, n - 1);
            }
        }
        for(int j = 0; j < n; ++ j) {   //遍历每一列的首尾，随意为O的位置深度遍历
            if(board[0][j] == 'O') {
                change(board, 0, j);
            }
            if(board[m - 1][j] == 'O') {
                change(board, m - 1, j);
            }
        }
        for(int i = 0; i < m; ++ i) {   //最后遍历所有位置，将V改成O，将O改成X即可
            for(int j = 0; j < n; ++ j) {
                if(board[i][j] == 'V') {
                    board[i][j] = 'O';
                } else if (board[i][j] == 'O') {
                    board[i][j] = 'X';
                }
            }
        }
    }
};