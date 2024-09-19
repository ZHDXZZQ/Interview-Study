/*
    思路： 有限自动机，时间Omn，空间O1
*/

class Solution {
public:
    vector<int> printMatrix(vector<vector<int> > matrix) {
        int up = 0 , left = 0;
        int down = matrix.size() - 1 , right;
        if(down == -1) return {};
        else right = matrix[0].size()-1;   //特殊情况考虑
        vector<int> res;
        char flag = 'r';  //四种标志代表本次向哪个方向遍历
        while(up <= down && left <= right){  //边界模拟up down left right代表的是当前可遍历到的边界
            if(flag == 'r'){
                for(int i = left; i <= right; i ++) res.push_back(matrix[up][i]);
                up ++;
                flag = 'd';
            }
            else if(flag == 'd'){
                for(int i = up; i <= down; i ++) res.push_back(matrix[i][right]);
                right --;
                flag = 'l';
            }
            else if(flag == 'l'){
                for(int i = right; i >= left; i --) res.push_back(matrix[down][i]);
                down --;
                flag = 'u';
            }
            else if(flag == 'u'){
                for(int i = down; i >= up; i --) res.push_back(matrix[i][left]);
                left ++;
                flag = 'r';
            }
        }
        return res;
    }
};