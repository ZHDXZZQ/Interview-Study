/*
    思路： DFS回溯，时间C 9 K，空间（C 9 K） * K，C 9 K代表组合数下9上K，k最大为9
    1. 回溯经典题，记录当前需要记录的数字和判断条件
    2. 如果满足条件则把结果插入，否则继续
    3. 每次递归从当前数字往后遍历，避免重复
    4. 如果满足条件则插入当前数字，进入dfs
    5. 每次dfs完这个数字后，把这个数字弹出进行回溯
*/

class Solution {
public:
    vector<vector<int>> res;    // 结果
    vector<int> cur_res;        // 当前符合要求的临时结果

    void dfs(int num, int remain, int step) {
        remain -= num;  // 剩余值先减去本次要插入的数字
        if (remain == 0 && step == 0) { // 如果满足剩余值为0，且满足要求数字的个数，则插入当前结果
            res.push_back(cur_res);
            return;
        }
        for (int j = num + 1; j <= 9; ++ j) {   // 否则的话从当前数字往后遍历，避免数字重复
            cur_res.push_back(j);   // 先把这个数字插入临时结果
            if (remain - j >= 0 && step > 0) {  // 满足条件则进入判断
                dfs(j, remain, step - 1);
            }
            cur_res.pop_back(); // 把这个数字弹出，回溯
        }
    }
    vector<vector<int>> combinationSum3(int k, int n) { 
        for (int i = 1; i <= 9; ++ i) { // 遍历9个数字，依次插入dfs回溯
            cur_res.push_back(i);
            if (n - i >= 0) {
                dfs(i, n, k - 1);
            }
            cur_res.pop_back();
        }
        return res;
    }
};