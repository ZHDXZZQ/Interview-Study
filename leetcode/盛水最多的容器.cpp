// 思路： 双指针，时间On，空间O1
// 1. 双指针指向两个边界，每次计算当前边界内的面积，更新答案
// 2. 难点在移动指针上，如果只想遍历一次，则需要考虑此时移动左指针还是右指针
// 3. 这里思考下，当前柱子一定是一个高一个低，因为如果是同样高的柱子移动哪个就无所谓了
// 4. 原因是，当你移动的是那个更高的柱子的话，另一保留的边界就是矮柱子，那么当你移动后是一个更高的柱子后，
// 当前的面积就是刚才那个矮柱子的高 * 更短一截儿的底，面积只会变得更小。
// 5. 而如果你移动的是更矮的柱子，当碰到一个更高的柱子时，这个边界就会变成刚才一个更高的柱子 * 变短一截儿的底
// 这样就还可能导致面积变大。

class Solution {
public:
    int maxArea(vector<int>& height) {
        int res = 0;
        int n = height.size();
        int left = 0;           //双指针指定两个边界
        int right = n - 1;
        while(left < right) {   //只要还没重合就继续计算
            int area = min(height[left], height[right]) * (right - left);       //计算当前边界的面积
            res = max(res, area);   //更新答案
            if(height[right] < height[left]) -- right;      //移动更矮的那个柱子的边界
            else ++ left;
        }
        return res;
    }
};