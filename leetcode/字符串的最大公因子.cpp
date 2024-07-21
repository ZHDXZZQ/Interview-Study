/*
    思路： 最大公约数，时间On，空间On，主要用于两个字符串拼接比较
    1. 如果两个字符串都有子字符串t构成，那么str1 = x*t，str2 = y*t
    2. 因此，一定有str1 + str2 = str2 + str1 = (x + y)*t
    3. 所以如果正反拼接结果不同，则不存在最大公因串
    4. 如果相同，我们求出最大公约数，两个串的最大公因串长度一定是最大公约数
    5. 因为两个数的约数一定是最大公约数的约数
    6. 如果有更小的公约数子串能构成两个字符串，那么最大公约数也是这个更小的子串可以构成的
    7. 因此，一定有n个小的公约数子串构成最大公约数子串
    8. 所以如果存在，最大公因数子串一定就是答案
*/

class Solution {
public:
    int gcd(int a, int b) { // 欧几里得算法
        return b ? gcd(b, a % b) : a;
    }

    string gcdOfStrings(string str1, string str2) {
        int m = str1.size();
        int n = str2.size();
        if (str1 + str2 != str2 + str1) {   // 正反不同则不存在
            return "";
        }
        string res = str1.substr(0, gcd(m, n)); // 否则截取任一串的前最大公约数个字符，就是答案
        return res;
    }
};