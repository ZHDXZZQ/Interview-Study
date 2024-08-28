/*
    思路： dfs，时间O2^n，空间O2^n
    1. 有效括号，即左括号与右括号总量相等，并且任意前缀中，左括号数量大于等于右括号
*/

class Solution {
public:
    vector<string> res;
    int size;
    // s为原串，pos为当前遍历位置，cur_res为当前结果，cnt为当前结果中左括号-右括号的数量
    // canDelL为还可以删掉的左括号数量，canDelR为还可以删掉的右括号数量，这两个用于剪枝判断
    void dfs(string& s, int pos, string cur_res, int cnt, int canDelL, int canDelR) {
        if (pos == size) {  // 如果已经遍历完
            if (cnt == 0) { // 如果此时左右括号数量是相同的，则插入结果
                res.push_back(cur_res);
                return;
            }
            return ;
        }

        if (s[pos] != '(' && s[pos] != ')') {   // 如果是普通字符，直接开始下一轮
            dfs(s, pos + 1, cur_res + s[pos], cnt, canDelL, canDelR);
        } else if (s[pos] == '(') { // 如果是左括号
            int end = pos;
            while (end < size && s[end] == '(') {
                ++ end; // 找到此位置开始连续的左括号，因为可能要删掉这些左括号
            }
            canDelL -= end - pos;   // 当前位置可以删除的左括号先把连续的全部减去
            for (int i = end - pos; i >= 0; -- i) { // 遍历删掉这些左括号的各种情况
                if (canDelL >= 0) { // 如果删掉这么多个左括号没有导致左括号失衡，dfs
                    dfs(s, end, cur_res, cnt, canDelL, canDelR);
                }
                cur_res += '('; // 每结束一轮，加回来一个
                ++ cnt; // 每加回来一个左括号，左括号-右括号的数量就+1
                ++ canDelL; // 后面要删掉的左括号加回来一个
            }
        } else if (s[pos] == ')') { // 如果是右括号
            int end = pos;  // 找到连续右括号
            while (end < size && s[end] == ')') {
                ++ end;
            }
            canDelR -= end - pos;
            for (int i = end - pos; i >= 0; -- i) { // 一个个记录删去不同个数的不同情况
                if (cnt < 0) {  // 左括号-右括号的数量如果为负，当前序列就不满足规则了
                    return;
                }
                if (canDelR >= 0) { // 能删除的右括号要满足数量
                    dfs(s, end, cur_res, cnt, canDelL, canDelR);
                }
                cur_res += ')'; // 加回来一个右括号
                -- cnt; // 左括号-右括号数量-1
                ++ canDelR; // 能删掉的右括号+1
            }
        }
    }

    vector<string> removeInvalidParentheses(string s) {
        size = s.size();
        int LsubR = 0;  // 当前左括号-右括号的数量
        int needToDelR = 0; // 当前要删掉的右括号的数量，即多余的右括号总量
        for (auto& c : s) {
            if (c == '(') { // 左括号直接插
                ++ LsubR;
            } else if (c == ')') {  // 如果是右括号
                if (LsubR == 0) {   // 如果前面左括号没有多余的了
                    ++ needToDelR;  // 这个右括号需要删掉
                } else {    // 如果前面还有可以匹配的右括号
                    -- LsubR;   // 左括号-右括号的数量-1
                }
            }
        }
        dfs(s, 0, "", 0, LsubR, needToDelR);    // 深度优先搜索
        return res;
    }
};