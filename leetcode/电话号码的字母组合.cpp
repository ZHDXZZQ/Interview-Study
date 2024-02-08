// 思路： 经典dfs回溯，时间O3^m * 4^n，空间Om + n，m为输入中键盘对应三个字符的键的个数，n为对应4个字符的
// 1. 每次遍历当前按键所有的可能性，并且对于每个可能性都遍历后续所有按键对应的所有可能性

class Solution {
public:
    vector<string> rec = {"", "", "abc", "def", "ghi", "jkl", "mno" , "pqrs", "tuv", "wxyz"};   //模拟手机按键
    vector<string> res; //全局记录答案

    void dfs(string cur_str, int cur_pos, string& digits) {
        int n = digits.size();
        if(cur_pos >= n) res.push_back(cur_str);    //如果当前位置已经超过了范围，把当前的组合插入结果
        else {
            char cur_key = digits[cur_pos];     //记录当前按下的是哪个键
            for(auto c : rec[cur_key - '0']) {  //遍历该键所代表的所有字符
                dfs(cur_str + c, cur_pos + 1, digits);  //每次都插入到当前字符的后面开启下一轮
            }
        }
    }

    vector<string> letterCombinations(string digits) {
        if(digits.size() == 0) return {};
        dfs("", 0, digits);
        return res;
    }
};