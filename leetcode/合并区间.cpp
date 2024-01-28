// 思路： 排序后拼接，时间Onlogn（排序耗时），空间Ologn（排序占地）
// 1. 首先对每对组合按第一个数字的大小排序
// 2. 定义当前的左端点数值和右端点数值
// 3. 遍历二维数组，判断每对的左端点是否在前面记录的右端点之外，如果在之外说明前面的是一个区间，此时插入左右端点，并更新左右端点为当前组合对的两个数字
// 4. 如果当前组合的第一个数小于现记录的右端点，说明该区间能融合进前面的区间，此时判断该组合的第二个数
// 5. 如果第二个数小于右端点，则包含在前面的区间，不用管。否则更新现记录的右端点
// 6. 最后再插入一次最后未插入的区间即可

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> res;
        sort(intervals.begin(), intervals.end());       //按每个vec第一个数字排序
        int left = intervals[0][0], right = intervals[0][1];    //初始化当前左右端点
        for(auto& p : intervals) {          //遍历每对vec
            if(p[0] > right) {              //如果第一个数大于右端点，表明无法和前面的区间融合
                res.push_back({left, right});   //插入前面的区间，并更新当前左右端点
                left = p[0];
                right = p[1];
            } else {                        //否则判断第二个数和右端点
                if(p[1] < right) {          //如果小于，表明包含在前面的区间
                    continue;
                } else {
                    right = p[1];           //否则更新当前左右端点区间
                }
            }
        }
        res.push_back({left, right});       //插入最后一组区间
        return res;
    }
};