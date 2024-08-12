/*
    思路： 中心扩展，时间On²，空间O1
    1. 遍历所有字符，每次判断以该字符为中心的奇数长度和偶数长度的字符串是否为回文子串
*/

class Solution {
public:
    int countSubstrings(string s) {
        int n = s.size();
        int res = 0;
        for (int i = 0; i < n; ++ i) {
            for (int j = i, k = i; j >= 0 && k < n; -- j, ++ k) {   // j和k从同一个字符同步向两边扩展，判断对象为奇数字符的字符串
                if (s[j] == s[k]) { // 如果该串为回文子串，结果+1，继续向两边扩展
                    ++ res;
                } else {
                    break;
                }
            }
            for (int j = i, k = i + 1; j >= 0 && k < n; -- j, ++ k) {   // 同上，判断对象为偶数字符的字符串
                if (s[j] == s[k]) {
                    ++ res;
                } else {
                    break;
                }
            }
        }
        return res;
    }
};