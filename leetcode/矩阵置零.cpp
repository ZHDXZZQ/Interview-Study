// 思路： 标记法， 时间Omn，空间O1
// 1. 首先用一个标志来记录第一列是否有0，如果有0在最后第一列统一全部变成0
// 2. 每行的第一列用来记录该行是否有0，如果有0则该行最后全部变成0
// 3. 然后从第二列开始，每列的第一行用来记录该列是否有0，如果有0将该列全部变为0
// 4. 首先从第二列开始把每列的0改完，然后从第一行开始把每行的0改完
// 5. 最后将第一列是否变0，结束

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int first_col = 0;          //第一列是否0
        int m = matrix.size();
        int n = matrix[0].size();
        for (int i = 0; i < m; ++ i) {  //遍历每一行的第一列
            if (matrix[i][0] == 0) {    //只要有一个为0，则标志置为1，最终将该列置0
                first_col = 1; 
            }
            for (int j = 1; j < n; ++ j) {  //遍历每一行，只要有一个为0，将该行第一列的值改为0
                if(matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                }
            }
        }
        for (int i = 1; i < n; ++ i) {  //从第二列开始，遍历每一列
            for (int j = 1; j < m; ++ j) {  //如果有0，则把该列的第0行置为0
                if (matrix[j][i] == 0) {
                    matrix[0][i] = 0;
                }
            }
        }
        for (int i = 1; i < n; ++ i) {  //遍历每一列，如果该列第一行为0
            if (matrix[0][i] == 0) {    //将该列全部置为0
                for (int j = 1; j < m; ++ j) { 
                    matrix[j][i] = 0; 
                }
            }
        }
        for (int i = 0; i < m; ++ i) {  //遍历每一行，如果该行第一列为0
            if (matrix[i][0] == 0) {
                for (int j = 1; j < n; ++ j) {  //将该行全部置为0
                    matrix[i][j] = 0; 
                }
            }
        }
        
        if(first_col == 1) {        //如果第一列需要置0，则全部改为0
            for(int i = 0; i < m; ++ i) { 
                matrix[i][0] = 0;
            }
        }
        return;
    }
};