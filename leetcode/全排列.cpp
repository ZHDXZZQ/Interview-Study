// 思路： 回溯，时间On x n！，空间On
// 1. 对于每个位置，依次选择每一个数进行填充，并用一个数组记录该数是否已被使用
// 2. 在这个位置使用完该数以后，要恢复现场以供下一个数使用该位置，以及后面的位置可以使用前面的数

class Solution {
public:
    vector<vector<int>> res;
    vector<int> cur_res;        //存储当前结果
    vector<bool> used_tag;      //记录该位置数字是否被使用

    void dfs(vector<int>& nums, int pos) {
        if(pos == nums.size()) {        //如果当前待插入位置超过大小，则把当前结果作为一种结果插入最终结果中
            res.push_back(cur_res);
            return;
        }

        for(int i = 0; i < nums.size(); ++ i) { //否则对该位置遍历所有数字，将可用的数字插入该位置，进行后续dfs
            if(used_tag[i] == false) {      //该数可用
                cur_res[pos] = nums[i];     //该位置插入该数
                used_tag[i] = true;         //标记已使用
                dfs(nums, pos + 1);         //对下一个位置进行插入
                used_tag[i] = false;        //恢复现场，标记该数使用完毕
                cur_res[pos] = -999;        //该位置恢复默认值
            }
        }
        return;
    }

    vector<vector<int>> permute(vector<int>& nums) {
        int n = nums.size();
        used_tag = vector<bool> (n, false); //初始化标记和当前结果数组
        cur_res = vector<int> (n, -999);
        dfs(nums, 0);       //开启递归
        return res;
    }
};