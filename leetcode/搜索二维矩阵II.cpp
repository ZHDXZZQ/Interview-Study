/*
    思路： 从右上角遍历，时间Om+n，空间O1
    1. 行列都是有序递增，如果从头开始可能无法确定走右边还是走下边
    2. 从右上角开始，大的数往下走，此时上一行一定都是更小的数字，无需考虑
    3. 小的数往左走，因为上一行已经被抛弃
*/

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();
        int i = 0, j = n - 1;
        while (j >= 0 && i < m) {
            if (matrix[i][j] == target) {
                return true;
            } else if (matrix[i][j] > target) {
                -- j;
            } else {
                ++ i;
            }
        }
        return false;
    }
};