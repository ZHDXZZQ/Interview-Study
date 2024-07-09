/*
    思路： 双指针，时间On，空间O1
    1. 首尾向中间遍历，对于遇到的元音字母对换
    2. 反转：前后元音字母一一兑换
*/

class Solution {
public:
    bool is_yuan(char& c) {
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c =='u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c =='U') {
            return true;
        }
        return false;
    }
    string reverseVowels(string s) {
        int n = s.size();
        int l = 0, r = n - 1;
        while (l < r) {
            if (is_yuan(s[l]) && is_yuan(s[r])) {
                swap(s[l], s[r]);
                ++ l;
                -- r;
            } else if (is_yuan(s[l])) { // 如果当前有一个是元音字母，只动另一个
                -- r;
            } else if (is_yuan(s[r])) {
                ++ l;
            } else {
                -- r;
                ++ l;
            }
        }
        return s;
    }
};