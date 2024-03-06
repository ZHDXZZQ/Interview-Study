// 思路： 动态规划，时间On²，空间On
// 1. 利用动态规划数组dp来表示每个位置的状态，如果该位置为true，表示该位置及之前所有位置一起可以被成功组成

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict;         //记录wordDict的每个字符串，方便查找
        for(auto& word : wordDict) dict.insert(word);
        int n = s.size();
        vector<bool> dp(n + 1, false);      //定义动态规划状态表示数组
        s = ' ' + s;                        //把字符串往后挪一个位置，方便后续判断
        dp[0] = true;                       //初始化前面这个空格的状态
        for(int i = 0; i < n; ++ i) {       //遍历每个字符
            if(dp[i]) {                     //如果该字符为true，表示该字符及之前的部分可以由dict的字符串组成
                for(int j = i + 1; j <= n ; ++ j) { //从该字符之后一一截取字符串
                    string cur_word = s.substr(i + 1, j - i);   //记录截取的当前字符串
                    if(dict.find(cur_word) != dict.end()) {     //如果当前字符串可以在dict中找到
                        dp[j] = true;                           //因为之前可以被组成，该被截取的部分也可被组成，所以到目前为止都可以被组成
                    }
                    if(dp[n]) return true;              //如果已经遍历到了最后一个字符，且判断为true，则所有都可被组成。
                }                           //否则从i往后继续寻找所有字符串
            }
        }
        return false;
    }
};