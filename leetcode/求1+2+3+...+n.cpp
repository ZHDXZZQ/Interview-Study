/*
    思路： 递归，时间On，空间On
*/

class Solution {
public:
    int Sum_Solution(int n) {
        n && (n += Sum_Solution(n-1));  //n=0时为假，右边就不会进入递归了。
        return n;
    }
};