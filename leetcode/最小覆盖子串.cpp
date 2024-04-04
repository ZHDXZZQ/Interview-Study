// 思路： 滑动窗口， 时间On，n为两个字符串的长度，空间O1，只需要记录两个串中对应的字符出现个数
// 1. 利用滑动窗口，首先记录t中的字符和出现个数，然后对s构造窗口
// 2. 记录窗口中字符的个数，如果该字符的个数还没有达到t中出现的次数，则记录成功匹配一个
// 3. 每次把窗口左端的多余字符排除掉，更新答案

class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> char_in_s, char_in_t;
        // s记录s中每个字符出现的次数，t记录t中每个字符出现的次数
        for (auto& c : t) {
            ++ char_in_t[c];
        }
        string res;
        int match_cnt = 0;  //记录当前s窗口中匹配的字符个数
        for (int l = 0, r = 0; r < s.size(); ++ r) {
            char& char_r = s[r];
            char& char_l = s[l];
            ++ char_in_s[char_r];   //新滑到的右边字符进入窗口
            if (char_in_s[char_r] <= char_in_t[char_r]) {
                ++ match_cnt;       //如果新进入的字符并不是多余的，则记录匹配成功一个
            }
            while (char_in_s[char_l] > char_in_t[char_l]) {
                -- char_in_s[char_l];   //将左边的多余字符依次移出窗口
                ++ l;
                char_l = s[l];
            }
            if (match_cnt == t.size()) {    //如果当前匹配的字符与t中的字符数量相同
                if (res.empty() || res.size() > r - l + 1) {
                    res = s.substr(l, r - l + 1);   //如果更短或者还没有答案，则更新答案
                }
            }
        }
        return res;
    }
};