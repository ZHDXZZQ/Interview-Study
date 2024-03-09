// 思路： 回溯，时间Os（所有可行解的长度之和），空间Otarget
// 1. 每次对每个数尝试不超过目标值的最多次数的插入，每次去探寻下一个位置的数能插入多少个
// 2. 遍历完一个位置后依次退出进行回溯

class Solution {
public:
    vector<vector<int>> res;
    vector<int> cur_res;

    void dfs(int pos, vector<int>& candidates, int remain) {    //pos代表当前查找的数组的位置，remain为对目标值的差值
        if(remain == 0) {           //如果差值恰好为0，则表示该解成立
            res.push_back(cur_res); //当前当解插入结果中
            return;
        }
        if(pos == candidates.size()) {  //如果当前位置已经超过了数组范围，不继续搜索
            return;
        }
        int cur_num = candidates[pos];  //选择当前的数，看看能插入几个
        for(int i = 0; cur_num * i <= remain; ++ i) {   //判断插入i个该数，如果值没超过当前差值，则插入i个该数
            dfs(pos + 1, candidates, remain - cur_num * i); //插入i个该数，搜索下个位置
            cur_res.push_back(cur_num);                 //把当前数插入1次，判断下轮是否还能插入1个（其实已插入i个该数）
        }
        for(int i = 0; cur_num * i <= remain; ++ i) {   //回溯，把插入的i个数全部退出
            cur_res.pop_back();
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        dfs(0, candidates, target);
        return res;
    }
};