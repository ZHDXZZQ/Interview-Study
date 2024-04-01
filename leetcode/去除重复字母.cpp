// 思路：贪心+单调栈， 时间On，空间On
// 1. 按序插入字母，如果待插字母字典序小于当前已插入字符的最后一个，那么考虑能否替换掉前面的字符
// 2. 如果尾部的字符在后面还有相同的字符，则替换掉
// 3. 如果待插入字符的字典序更大，则先将其插入，后面还有可能会被弹出

class Solution {
public:
    string removeDuplicateLetters(string s) {
        unordered_map<char, int> ch_cnt;        //记录每个字符有多少个
        unordered_map<char, bool> is_used;      //记录该字符是否已被插入过
        for (auto& c : s) {
            ++ ch_cnt[c];
        }
        string res;                 //已插入的字符，即结果，看作一个单调栈
        res.push_back(s[0]);        //初始化先插入一个字符
        int s_ptr = 1;              //遍历原始串的指针
        while (s_ptr < s.size()) {
            if (res.empty()) {      //如果当前结果中为空（对应全部被弹出的情况
                res.push_back(s[s_ptr]);    //将当前遍历的字符插入
                ++ s_ptr;
                continue;
            }
            if (is_used[s[s_ptr]] == true) {    //如果当前待插入字符已被插入过，跳过
                -- ch_cnt[s[s_ptr]];        //当前字符数量-1
                ++ s_ptr;
                continue;
            }
            if (s[s_ptr] - res.back() > 0) {    //如果待插入字符字典序大
                is_used[res.back()] = true;     //将当前尾部字符置为true
                res.push_back(s[s_ptr]);        //将该字符插入
                ++ s_ptr;
                continue;
            }
            if (s[s_ptr] == res.back()) {       //如果字典序相同
                ++ s_ptr;                       //跳过该字符，可用数量-1
                -- ch_cnt[res.back()];
                continue;
            }
            if (s[s_ptr] - res.back() < 0) {    //如果字典序小
                if (ch_cnt[res.back()] < 2) {   //如果当前结尾后面已经没有可支配的数量
                    is_used[res.back()] = true; //直接插入，不必弹出
                    res.push_back(s[s_ptr]);
                    ++ s_ptr;
                } else {
                    -- ch_cnt[res.back()];      //如果后面还有相同字符，数量-1
                    is_used[res.back()] = false;    //将该尾巴弹出，并标为false
                    res.pop_back();
                }
            }
        }
        return res;
    }
};