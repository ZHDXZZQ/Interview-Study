/*
    思路： 贪心，时间On，空间O1
    也可以动规，比较麻烦。
    1. 经过不等式计算，当全部拆成3时，乘积最大
    2. 当最后一个不够3，拆成一个1时，补到一个3的后面，将其变成4
    3. 拆成一个2时，单独留下来计算
*/

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param n int整型 
     * @return int整型
     */
    int cutRope(int n) {
        // write code here
        int count = 0;  // 记录3的个数
        while (n >= 3) {    // 拆3
            n -= 3;
            ++ count;
        }
        if (n == 1) {   // 还剩下一个1，补到1个3上计算结果
            return pow(3, count - 1) * 4;
        } else if (n == 2) {    // 剩下一个2时，直接计算
            return pow(3, count) * 2;
        }
        return pow(3, count);
    }
};