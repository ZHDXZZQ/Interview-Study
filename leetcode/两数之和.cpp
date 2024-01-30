// 思路： 哈希表，时间On，空间On
// 1. 力扣的开端之题，有无数种方法，这里讲解最优解
// 2. 用哈希表记录数组中的数字及其下标
// 3. 遍历全部数字并将其存入哈希表，并寻找相加能得到目标值的数字，返回二者的下标

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> num_umap;   //记录已有的数及其下标
        for (int i = 0; i < nums.size(); ++ i) {
            auto& cur_num = nums[i];
            if (num_umap.find(target - cur_num) != num_umap.end()) {    //如果有某个数相加等于目标值
                return {num_umap[target-cur_num], i};       //返回二者的下标
            } else {    //否则将该数存储umap中，因为结果只有一个，所以无需考虑重复
                num_umap[cur_num] = i;
                // num_umap.insert(make_pair(cur_num, i));
                // num_umap.emplace(make_pair(cur_num, i));
                // 多种插入写法，也可以带上move
            }
        }
        return {};  //此处随便写，因为必有答案
    }
};