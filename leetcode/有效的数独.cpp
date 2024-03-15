// 思路： 哈希表遍历， 时间O1,空间O1，遍历三遍全表，最多用9个额外空间
// 1. 遍历每一行，用哈希表存储每个数字，如果数字已存在则false
// 2. 遍历每一列，用哈希表存储每个数字，如果数字已存在则false
// 3. 遍历每个九宫格，用哈希表存储每个数字，如果数字已存在则false

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        for(int i = 0; i < 9; ++ i) {
            unordered_set<char> col_rec, row_rec;   //行哈希表和列哈希表
            for(int j = 0; j < 9; ++ j) {
                int row_num = board[i][j];          //取出每个位置的值
                int col_num = board[j][i];
                if(col_rec.find(col_num) == col_rec.end() && col_num != '.') {  //如果表中没有且不为空
                    col_rec.insert(col_num);        //将其插入
                } else if(col_rec.find(col_num) != col_rec.end()) { //如果不是空且表中已有，返回false
                    return false;
                }
                if(row_rec.find(row_num) == row_rec.end() && row_num != '.') {  //对每一行判断
                    row_rec.insert(row_num);
                } else if(row_rec.find(row_num) != row_rec.end()) {
                    return false;
                }
            }
        }
        for(int i = 0; i < 3; ++ i) {
            int row = 3 * i;        //row和col表示每个九宫格的左上角
            for(int j = 0; j < 3; ++ j) {
                int col = j * 3;
                unordered_set<char> rec;
                for(int x = 0; x < 3; ++ x) {
                    for(int y = 0; y < 3; ++ y) {
                        int num = board[row + x][col + y];  //每个九宫格一个哈希表来判断
                        if(num == ',') continue;
                        if(rec.find(num) == rec.end() && num != '.') {
                            rec.insert(num);
                        } else if(rec.find(num) != rec.end()) {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }
};