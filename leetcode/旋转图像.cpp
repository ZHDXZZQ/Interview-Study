// 思路： 翻转代替旋转，时间On²，空间O1
// 1. 沿主对角线翻转
// 2. 沿中轴左右翻转
// 3. 上述二者的顺序可以任意，两次翻转后即可实现顺时针旋转90度的效果

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        for(int i = 0; i < n; ++ i) {       //沿主对角线翻转
            for(int j = i + 1; j < n; ++ j) {
                swap(matrix[i][j], matrix[j][i]);
            }
        }
        for(int i = 0; i < n; ++ i) {       //沿中轴左右翻转
            for(int j = 0; j < (n / 2); ++ j) {
                swap(matrix[i][j], matrix[i][n - j - 1]);
            }
        }
    }
};