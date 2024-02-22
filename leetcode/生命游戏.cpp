// 思路： 添加新的标志，时间Omn（每个格子被遍历10遍），空间O1
// 1. 需要记录当前各自现在的状态，以及变化后的状态
// 2. 因此需要加一些标志来同时表示现在的状态和变化后的状态
// 3. 比如，当前位为0，如果接下来还是死亡，则不变，如果要复活，则变成2
// 4. 当前位为1，如果接下来还活着，则不变，如果要死亡则变成3
// 5. 这样遍历的时候后面的格子就不受当前格子变化的影响，而可以直接使用以前的状态
// 6. 最后再把2和3变成1和0即可
// 7. 简便写法就是用二进制数位的思想，最后一位表示当前状态的死活，倒数第二位表示下一状态的死活，这样直接用与和或操作就可以完成判断

class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        //当前位置为0，如果接下来要死不变，要活就变成2
        //当前位置为1，如果接下来要死就变成3，要活就不变
        int m = board.size();
        int n = board[0].size();
        int dx[8] = {0, 0, 1, 1, 1, -1, -1, -1};    //记录八种方向
        int dy[8] = {1, -1, 0, 1, -1, 0, 1, -1};
        for(int i = 0; i < m; ++ i) {               //遍历每个格子
            for(int j = 0; j < n; ++ j) {
                int live_cnt = 0, dead_cnt = 0;     //记录当前格子周围8个格子的活死细胞数量
                for(int k = 0; k < 8; ++ k) {
                    int x = i + dx[k];              //遍历周围八个格子
                    int y = j + dy[k];
                    if(x < 0 || y < 0 || x >= m || y >= n) continue;    //如果越界则不考虑
                    if(board[x][y] % 2 == 0) ++ dead_cnt;   //否则记录格子当前状态的死活细胞数量
                    else ++ live_cnt;
                }
                if(board[i][j] == 0) {      //对当前格子做出改变
                    if(live_cnt == 3) board[i][j] = 2;
                } else {
                    if(live_cnt < 2 || live_cnt > 3) board[i][j] = 3;
                }
            }
        }
        for(int i = 0; i < m; ++ i) {       //遍历所有格子，把2和3改为1和0
            for(int j = 0; j < n; ++ j) {
                if(board[i][j] == 3) board[i][j] = 0;
                else if(board[i][j] == 2) board[i][j] = 1;
            }
        }
    }
};