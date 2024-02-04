// 思路： 哈希表，时间On，空间On
// 1. 遍历数组，对于每个被遍历到的数，判断是否在哈希表中
// 2. 如果不在，将该数及其最后出现的位置（即当前位置）存入哈希表中
// 3. 如果在，则计算当前位置和记录位置的差值是否满足要求，如果满足返回真
// 4. 任何情况下都重新记录该数的位置，因为只需要记录该数出现的最后位置即可

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> num_pos;
        for (int i = 0; i < nums.size(); ++ i) {
            auto& num = nums[i];
            if(num_pos.find(num) == num_pos.end()) {    //如果该数之前没出现过，将其存入
                num_pos[num] = i;
            } else {        //否则判断是否满足要求
                if(i - num_pos[num] <= k) return true;
                num_pos[num] = i;   //并更新该数出现的最后位置
            }
        }
        return false;
    }
};