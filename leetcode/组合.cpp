// 思路： 回溯递归， 时间O（cnk）k = n个里面选k个，选k次；空间Ok+n 递归栈空间和临时结果
// 1. 保证每个数不重复的情况下，按递增的序列依次选择每个数，当数满时插入一组答案，然后回溯接着遍历下一种情况

class Solution {
public:
    vector<vector<int>> res;
    vector<int> cur_res;            //存储当前情况的临时结果

    void dfs(int pos, int& n, int& k) { //pos为当前待插入的位置
        if(pos == k) {              //如果pos已经等于k表明当前临时结果大小已经为k个，无需插入
            res.push_back(cur_res);
            return;
        }
        int num = 1;                //当前情况该寻找的第一个数
        if(!cur_res.empty()) {      //如果是第一次进来，则初始值为1，否则为临时结果的末尾值+1
            num = cur_res.back() + 1;   //因为2，1和1，2属于重复结果，只能插入一种，因此我们按增序插入
        }
        for(int i = num; i <= n; ++ i) {    //从num开始往后遍历，直到n，这里保证了结果增序，不会有重复结果
            cur_res.push_back(i);           //将该值插入临时结果中
            dfs(pos + 1, n, k);             //pos+1开启递归，寻找下一个插入位置的值
            cur_res.pop_back();             //回溯，当前位置可以使用下一个值了
        }
    }

    vector<vector<int>> combine(int n, int k) {
        dfs(0, n, k);
        return res;
    }
};