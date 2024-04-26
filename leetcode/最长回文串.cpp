// 思路： 模拟，利用回文串的性质，时间On，空间O52常数级
// 1. 记录每个字符的数量
// 2. 题目利用所有的字符构造一个最大的回文串，那么利用回文串轴对称的特点
// 3. 把每个字符的都提出来最大的偶数个，这两两一对一定能构成回文串
// 4. 如果还有单个的字符，则选1个加入进来作为中心的那个字符。如果没有的话偶数个字符也是回文串

class Solution {
public:
    int longestPalindrome(string s) {
        unordered_map<char, int> char_cnt;
        for (auto& c : s) { //记录每个字符出现的次数
            ++ char_cnt[c];
        }
        int res = 0;
        for (auto& [c, k] : char_cnt) { //遍历每个字符
            res += (k / 2) * 2; //将其取出最大的偶数对数，x2即为取出的字符个数
        }
        if (res < s.size()) {   //如果此时结果字符串的长度小于s，说明有一些单个字符无法使用
            ++ res; //任选一个即可
        }
        return res;
    }
};