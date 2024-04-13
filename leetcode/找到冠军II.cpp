// 思路： 找到入度为0的唯一点， 时间On，空间On
// 1. 记录每个点的入度
// 2. 判断所有点的入度，如果只有一个入度为0的点，则该点就是结果
// 3. 否则不存在冠军

class Solution {
public:
    int findChampion(int n, vector<vector<int>>& edges) {
        vector<int> in(n, 0);       //记录每个点的入度
        for (auto& vec : edges) {   //初始化入度
            auto& b = vec[1];
            ++ in[b];
        }
        bool is_zero = false;       //记录是否已有入度为0的点
        int res = -1;
        for (int i = 0; i < n; ++ i) {  //遍历所有点的入度
            if (in[i] == 0) {           //如果某个点的入度为0
                if (is_zero == false) { //如果是第一个点，则记录
                    res = i;
                    is_zero = true;
                } else {                //如果不是第一个点，那么就不存在唯一冠军
                    return -1;
                }
            }
        }
        return res;         //如果没有入度为0的点，则不存在冠军
    }
};