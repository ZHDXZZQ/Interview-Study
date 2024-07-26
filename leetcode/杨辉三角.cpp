/*
    思路： 简单模拟，时间On²，空间On
*/

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> res;
        for(int i = 0; i < numRows; i ++) {
            vector<int> temp;
            for(int j = 0; j <= i; j ++) {  // 几行就有几个元素
                if(j == 0 || j == i) {  // 首尾一定是1
                    temp.push_back(1);
                } else {    // 如果不是首尾就计算和
                    temp.push_back(res[i - 1][j - 1] + res[i - 1][j]);
                }
            }
            res.push_back(temp);
        }
        return res;
    }
};