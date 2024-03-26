// 思路： bfs宽搜， 时间On^n，空间On^n
// 1. 需要记录一些映射，比如从位置到id的映射，从位置到值的映射，从位置到到达这里最小步数的映射，从id到位置的映射
// 2. 以上映射主要是位置到id和id到位置，另外两个可以用位置或id来映射，灵活运用PII的vec和二维矩阵即可
// （id和位置是同一个含义，其他的所有映射都可以由id或位置作为key，id用PII的vec，位置用二维矩阵）
// 3. 首先把所有的映射做好，然后用一个队列开启宽搜
// 4. 每次找到对应的位置和id，往后走六步，每一步到达一个位置，碰到梯子到达梯子的位置
// 5. 如果该位置没有到达过，则进入队列
// 6. 如果某一步到达了最终位置，返回步数
// 7. 否则返回-1

#define x first
#define y second

typedef pair<int, int> PII;

class Solution {
public:
    int snakesAndLadders(vector<vector<int>>& board) {
        int n = board.size();
        int sum = n * n;                                    //以下记录的pos和id可以相互替换，pos映射利用二维矩阵，id映射利用PII的vector
        queue<PII> bfs_q;                                   //bfs使用队列
        vector<PII> id_pos(sum + 1);                         //记录当前位置的编号对应的位置
        unordered_map<int, int> id_steps;                        //记录当前位置以及到达当前位置的最小步数
        vector<vector<int>> pos_ids(n, (vector<int>(n, 0)));    //记录当前位置对应的编号
        unordered_map<int, int> id_vals;                         //记录当前位置的值
        bool turn_right = true;                                 //记录当前是从左往右还是从右往左，true为从左往右
        int id = 1;                                             //记录当前id
        for (int i = n - 1; i >= 0; -- i) {
            for (int j = turn_right ? 0 : n - 1; j >= 0 && j < n; j = turn_right ? j + 1 : j - 1) {      //遍历所有格子
                PII cur_pos = {i, j};           //当前位置
                id_pos[id] = cur_pos;           //记录id映射当前位置
                pos_ids[i][j] = id;             //记录当前位置映射id
                id_vals[id] = board[i][j];      //记录当前位置的值
                ++ id;
            }
            turn_right = !turn_right;           //转向
        }
        bfs_q.push({n - 1, 0});             //将左下角的起始点入队，开始bfs
        id_steps[1] = 0;                    //记录到达第一个点所需要的步数为0
        while (bfs_q.size()) {
            auto cur_pos = bfs_q.front();   //将队头取出
            bfs_q.pop();                    
            auto cur_id = pos_ids[cur_pos.x][cur_pos.y];    //队头的id
            auto cur_step = id_steps[cur_id];               //到达队头所在位置需要的步数
            for (int k = 1; k <= 6; ++ k) {                 //从该位置往后走六步
                auto next_id = cur_id + k;                      //记录下一步的id
                if (next_id == sum) { return cur_step + 1; }    //如果id到达终点，则返回
                auto next_pos = id_pos[next_id];            //下一步的位置
                if (id_vals[next_id] != -1) {               //如果下一步的值不为-1，则有梯子可走
                    next_id = id_vals[next_id];
                    next_pos = id_pos[next_id];             //更新从梯子到的位置和id
                    if (next_id == sum) { return cur_step + 1; }    //如果到达最终位置，返回
                }
                if (id_steps.find(next_id) == id_steps.end()) { //记录的前提是这个id没有走过，不然再走的话步数肯定更多，没有必要
                    bfs_q.push(next_pos);                   //否则的话插入到达的位置
                    id_steps[next_id] = cur_step + 1;       //记录到达的位置的步数
                }
            }
        }
        return -1;
    }
};