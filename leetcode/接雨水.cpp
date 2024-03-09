// 思路：单调栈， 时间On，空间On。
// 另有简化DP的空间O1解法，具体见官方讲解，思路大概为双指针向中间遍历利用两边最大值累计应该被接水的部分的面积
// 1. 对于高度来说，构造一个递减的单调栈
// 2. 如果碰到更高的柱子，则说明该位置可被接水，于是和上一个高一些的柱子比较，计算这里能接多少水
// 3. 一直向前比较直到栈空或该柱子低于之前的柱子，然后该柱子入栈开启下一个柱子的判断
// 4. 每次循环开启时保证栈中柱子的高度递减，且栈顶及之前的柱子之间保证无法再接水

class Solution {
public:
    int trap(vector<int>& height) {
        int res = 0;
        int n = height.size();
        if (n <= 2) return 0;       //只有两个柱子或更少则无法接水
        stack<int> des_sta;         //单调递减栈，存储每个柱子的下标
        des_sta.push(0);            //插入初始值0号柱子的下标0
        for (int i = 1; i < n; ++ i) {  //从1号柱子开始遍历
            int cur = height[i];        //记录当前柱子的高度
            while (cur >= height[des_sta.top()]) {  //如果当前柱子大于栈顶（即上一根最低的柱子）
                int top = des_sta.top();            //记录上一根最低的柱子
                des_sta.pop();                      //将其拿出，因为这里将被填水
                if (des_sta.empty()) break;         //如果栈此时已空，表明再往前没有柱子，该位置不可接水
                if (height[top] == cur) break;      //如果当前柱子和上一个最低的柱子相等，则该位置不可接水
                //以上两种情况虽不可接水，但也要将该柱子插入回栈顶，作为当前最低的柱子供后续判断
                int last = des_sta.top();           //记录再前一根柱子，现在要在这两根柱子间接水
                int h = min(height[last], cur) - height[top];   //计算接水面积的高度
                int width = i - last - 1;                       //计算接水面积的宽度
                res += h * width;                               //面积加上当前接水的面积
            }                       //循环遍历，直到前一个柱子比当前柱子高，保证这两个柱子之间已接满水
            des_sta.push(i);        //将当前柱子入栈
        }
        return res;
    }
};