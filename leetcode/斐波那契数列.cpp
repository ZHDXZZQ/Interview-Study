/*
    经典动规，三种解法。
*/

// 1. 递归。时间O2^n，空间On
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param n int整型 
     * @return int整型
     */
    int Fibonacci(int n) {
        // write code here
        if (n == 1 || n == 2) { return 1; }
        return Fibonacci(n - 1) + Fibonacci(n - 2);
    }
};



// 2. 动规。时间On，空间On
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param n int整型 
     * @return int整型
     */
    int Fibonacci(int n) {
        // write code here
        if (n == 1 || n == 2) { return 1; }
        vector<int> dp(2, 1);
        for (int i = 2; i < n; ++ i) {
            dp.push_back(dp[i - 1] + dp[i - 2]);
        }
        return dp[n - 1];
    }
};



// 3. 动规优化，时间On，空间O1
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param n int整型 
     * @return int整型
     */
    int Fibonacci(int n) {
        // write code here
        if (n == 1 || n == 2) { return 1; }
        int a = 1, b = 1;
        int res;
        for (int i = 2; i < n; ++ i) {
            res = a + b;
            a = b;
            b = res;
        }
        return res;
    }
};