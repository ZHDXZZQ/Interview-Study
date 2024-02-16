// 解法一：按右边界排序
// 思路： 排序+贪心， 时间Onlogn，空间Ologn，均为排序消耗
// 1. 按右边界排序，每次选中第一个右边界，依次判断该点是否在后面的区间内
// 2. 如果在，表明该区间可以一并被打爆，否则话，重新选择第一个右边界继续判断

class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        sort(points.begin(), points.end(), [](vector<int>& a, vector<int>& b) { //加引用避免超时
            return a[1] < b[1];     //按区间右边界排序
        });
        int res = 1, r = points[0][1];  //选择第一个右边界
        for (int i = 1; i < points.size(); ++ i)
            if (points[i][0] > r) { //如果当前右边界不在区间内
                ++ res;             //则需要多射一箭，并且更新当前判断用的右边界
                r = points[i][1];
            }
        return res;
    }
};



// 解法二：按左边界排序
// 思路： 排序+合并区间，时间Onlogn，空间On ，n为points的大小
// 1. 首先将所有区间按第一个值排序，然后遍历所有区间
// 2. 依次将有交集的区间进行交集部分合并，得到一个所有区间合并后的多个区间
// 3. 区间的个数即为答案

class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        vector<vector<int>> rec;
        sort(points.begin(), points.end());     //排序
        int first = points[0][0], second = points[0][1];    //记录当前待插入区间的首尾，用于判断是否有交集
        int n = points.size();
        for(int i = 1; i < n; ++ i) {
            vector<int>& pnt = points[i];
            if(pnt[0] <= second) {      //如果当前遍历到的区间和待插入区间有交集
                first = max(first, pnt[0]); //则更新头尾为二者的交集
                second = min(second, pnt[1]);
            } else {        //如果没有交集，则将待插入区间插入，并记录下一个待插入区间的头尾
                rec.push_back({first, second});
                first = pnt[0];
                second = pnt[1];
            }
        }
        rec.push_back({first, second}); //将最后一个待插入区间插入
        return rec.size();
    }
};