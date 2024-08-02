/*
    思路： DP，时间On根号n，空间On
    1. 计数类dp，可以先计算组成该数的所有种类，再依次从后计算前面的数字加上当前数字的结果
*/

class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;  // 0由0个平方数组成
        for (int i = 1; i <= n; ++ i) { // 计算每个数字由几个平方数组成
            for (int j = 1; j * j <= i; ++ j) { // 计算每个数字的平方
                dp[i] = min(dp[i], dp[i - j * j]);  // 组成当前数字的平方数的数量为将j*j作为一个完全平方数的情况下，记录上一个数字的最小组成，再加上当前的这个j*j，每次都取最小值
            }
            ++ dp[i];   // 加上最后一个数，得到组成i的平方数的最小数量
        }
        return dp[n];
    }
};

// 解法2
// 思路： 数学定理，时间O根号n，空间O1

// class Solution {
// public:
    
//     bool check(int m) {  //判断m是否是平方数
//         int i = sqrt(m);
//         return i * i == m;
//     }

//     int numSquares(int n) {  //只考虑正数
//         if(check(n)) { return 1; } //自己本身就是答案，返回1个

//         for(int i = 1; i < n / i; i ++) {
//             if(check(n - pow(i,2))) {
//                 return 2;
//             }
//         }
//         //如果n减去i平方还是平方数，那结果就是这两个数

//         while(n % 4 == 0) {
//             n /= 4;
//         }  //勒让德三平方和定理，先把4的j次除干净

//         if(n % 8 != 7) { return 3; }  //勒让德三平方和定理，剩余的数要满足8的k次+7，否则就是4

//         //当且仅当 n 不等于 4^k * (8m + 7) 时，n可以由1或2或3个正整数的平方相加得到
//         //若相等，就只能由4个得到

//         return 4;   //拉格朗日四平方和定理：任一个数最多由4个平方数相加得到
//     }
// };