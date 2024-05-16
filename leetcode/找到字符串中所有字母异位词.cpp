/*
    思路： 滑动窗口，时间Om+n，空间Oc，其中m和n为s和p的长度，c为p中的字符种类数，最多26
    1. 记录p中每种字符的个数
    2. 用滑动窗口记录当前窗口内各字符已出现的次数
    3. 每当有一个p中的字母被匹配完成时，计数器+1
    4. 当计数器与p中的字符个数相同时，记录当前的窗口左边界，作为一个答案
*/

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int cnt = p.size();
        int n = s.length();
        int l = 0, r = 0;
        unordered_map<char, int> c_cnt; // 记录每种字符在p中出现的次数
        for (auto& c : p) {
            ++ c_cnt[c];
        }
        int cur_cnt = c_cnt.size(); // 记录p中字符的种类个数
        if (n < cnt) {  // 特判
            return {};
        }
        while (r < cnt) {   // 将窗口右边界滑到右边
            if (c_cnt.count(s[r])) {    // 如果当前字符在p中出现过
                -- c_cnt[s[r]];     // 将其个数-1
                if (c_cnt[s[r]] == 0) { // 如果全部匹配完成
                    -- cur_cnt; // 总剩余个数-1
                }
            }
            ++ r;   // 右边界右滑
        }
        vector<int> res;
        if (cur_cnt == 0) { // 如果全部字符都匹配，记录当前作为一次结果
            res.push_back(l);
        }
        while (r < n) {
            if (c_cnt.count(s[l])) {    // 将左边界滑出，只有当其出现在p中时，才计算
                if (c_cnt[s[l]] == 0) { // 如果即将滑出的字符当前被匹配完
                    ++ cur_cnt;     // 那么剩余个数+1
                }
                ++ c_cnt[s[l]]; // 待匹配的字符+1
            }
            ++ l;   // 滑动左窗口
            if (c_cnt.count(s[r])) {    // 将右边界滑入，只有当其出现在p中时，才计算
                -- c_cnt[s[r]];     // 将其匹配个数-1
                if (c_cnt[s[r]] == 0) { // 如果当前字符匹配完
                    -- cur_cnt; //总剩余匹配个数-1
                } 
            }
            ++ r;   // 滑动右窗口
            if (cur_cnt == 0) { // 如果当前窗口内全部匹配
                res.push_back(l);   // 记录一次答案
            }
        }
        return res;
    }
};