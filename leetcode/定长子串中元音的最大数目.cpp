/*
    思路： 滑动窗口，时间On，空间O1
    1. 利用滑动窗口统计当前k个字符的元音字母的数量，并更新最大值
    2. 每次滑动一个字符
*/

class Solution {
public:
    bool is_yuan(char& c) { // 判断该字符是否是元音字母
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            return true;
        }
        return false;
    }

    int maxVowels(string s, int k) {
        int n = s.length();
        int l = 0, r = 0;   // 窗口左右端点
        int cnt = 0;    // 当前窗口内元音字母的数量
        while (r < k) { // 题目中k一定小于串长度n，所以无需判断越界
            if (is_yuan(s[r])) {    // 如果该字符是元音字母，则更新当前窗口内的元音字母的个数
                ++ cnt;
            }
            ++ r;
        }   // 初始化滑动窗口的大小为k，并记录最开始k个字母的元音字母的数量
        int res = cnt;    // 初始化结果
        while (r < n) { // 滑动到结尾
            if (is_yuan(s[l])) {    // 左端点滑出窗口
                -- cnt;
            }
            if (is_yuan(s[r])) {    // 右端点滑入窗口
                ++ cnt;
            }
            ++ r;   // 窗口移动一个字符
            ++ l;
            res = max(res, cnt);    // 更新当前窗口内的最大数量
        }
        return res;
    }
};