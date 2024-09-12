/*
    思路： 模拟，时间O10^n，空间O10^n
    1. 无需解释，理解题意即可秒
*/

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param n int整型 最大位数
     * @return int整型vector
     */
    vector<int> printNumbers(int n) {
        // write code here
        vector<int> res;
        for (int i = 1; i < pow(10, n); ++ i) {
            res.push_back(i);
        }
        return res;
    }
};