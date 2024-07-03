/*
    思路： 前缀和，时间On，空间O1
*/

class Solution {
public:
    int largestAltitude(vector<int>& gain) {
        int cur_hight = 0;
        int res = 0;
        for (auto& num : gain) {    // 只需从0统计每个节点的海拔，并找出最高海拔即可
            cur_hight += num;
            res = max(res, cur_hight);
        }
        return res;
    }
};