// 思路： 模拟，时间On，空间O1
// 1. 因为有序，拿新的区间和现有区间一一个比较，如果没有交集，则把小的那个直接插入结果。
// 2. 同步更新接下来要进行比较的区间，也就是待插入的区间
// 3. 如果有交集，则把接下来要插入的区间更新为有交集的二者的并集继续遍历

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> res;
        auto& cmp_vec = newInterval;        //每次拿待插入区间与现有区间进行比较
        for (auto& cur_vec : intervals) {   
            if (cmp_vec[0] > cur_vec[1]) {  //如果待插入区间左端点大于现有区间的右端点，则插入现有区间
                res.push_back(cur_vec);
            } else if (cmp_vec[1] < cur_vec[0]) {
                res.push_back(cmp_vec); //如果待插入区间右端点小于现有区间左端点，则插入待插入区间
                cmp_vec = cur_vec;      //并将现有区间更新为待插入区间
            } else {        //其他情况，表明待插入区间和现有区间有交集
                cmp_vec[0] = min(cmp_vec[0], cur_vec[0]);   //更新待插入区间的左右端点为二者的并集
                cmp_vec[1] = max(cmp_vec[1], cur_vec[1]);
            }
        }
        res.push_back(cmp_vec); //插入最后一个没有进行比较的待插入区间
        return res;
    }
};