// 思路： 从后往前遍历，时间On，空间O1
// 1. 先剔除尾部的空格
// 2. 然后向前遍历，直到遍历完整个串或者再次碰到空格为止
// 3. 记录长度

class Solution {
public:
    int lengthOfLastWord(string s) {
        int res = 0;
        int ptr = s.size() - 1;  //指针指向左后向前遍历
        while(ptr >= 0 && s[ptr] == ' ') {
            -- ptr;    //过滤掉尾部空格
        }
        while(ptr >= 0 && s[ptr --] != ' ') {
            ++ res;           //记录最后一个单词的长度
        }
        return res;
    }
};