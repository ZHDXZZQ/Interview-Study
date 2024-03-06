// 思路： 原地多维动态规划， 时间On²，空间O1
// 1. 每个位置表示从上往下走到该位置的最小和
// 2. 因为只能从头往下走，所以每行遍历即可

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        for(int i = 1; i < n; ++ i) {   //从第二行开始计算
            triangle[i][0] += triangle[i - 1][0];   //每行的开头只能从上一行的开头走到
            triangle[i][i] += triangle[i - 1][i - 1];   //每行的结尾只能从上一行的结尾走到
            for(int j = 1; j < i; ++ j) {   //对于每行的中间的位置，可以从上一行的该位置及上一行的前一个位置走到
                triangle[i][j] += min(triangle[i - 1][j - 1], triangle[i - 1][j]);  //选择一个值小的位置走过来，更新当前位置的值
            }
        }
        int res = INT_MAX;
        for(int i = 0; i < triangle[n - 1].size(); ++ i) {
            res = min(res, triangle[n - 1][i]);     //在最后一行中选择最小值返回
        }
        return res;
    }
};