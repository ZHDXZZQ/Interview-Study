/*
    思路： dfs，时间n*C下(n - 1)上3，最多只需要搜索前12个字符，因此n=12，最大10000，空间O1，最多递归4层栈空间
    具体看注释，稍微不太好思考的一个dfs题
*/
class Solution {
public:
    vector<string> res;
    int n;

    void dfs(string& s, int pos, int where, string temp) {
        if (pos == n) { // 如果当前搜索位置到达字符串末尾
            if (where == 4) {   // 并且是搜索完了四个部分，那么将最后一个.弹出，插入答案
                temp.pop_back();
                res.emplace_back(temp);
            }
            return;
        }
        if (where == 4) { return; } // 如果没搜完，但是已经超过四段，那么无需再搜
        for (int i = pos, num = 0; i < n; ++ i) {   // 从当前位置往后选数字
            if (i > pos && s[pos] == '0') { // 如果有前导0，则不继续选择
                break;
            }
            num = num * 10 + s[i] - '0';    // 否则选择一个数字
            if (num <= 255) {   // 如果数字符合要求
                dfs(s, i + 1, where + 1, temp + to_string(num) + '.');  // 把这个数字作为一个部分插入，搜索下一个部分
            } else {
                break;  // 如果当前数字已经超过大小，则不继续搜索
            }
        }
    }
    
    vector<string> restoreIpAddresses(string s) {
        n = s.size();
        dfs(s, 0, 0, "");
        return res;
    }
};