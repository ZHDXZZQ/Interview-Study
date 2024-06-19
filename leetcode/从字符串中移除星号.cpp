/*
    思路： 模拟栈，时间On，空间On。也可以用双指针实现空间O1的解法
    1. 利用指针表示当前应该插入的字符的位置
    2. 遍历每个字符，如果为*，则删除前一个字符，体现为指向结尾的指针回退
    3. 如果是正常字符，则将该字符插入到当前位置
*/

class Solution {
public:
    string removeStars(string s) {
        string res(s.size(), '.');  // 初始化结果字符串，长度为输入字符串的长度
        int pos = 0;    // 定义当前应该插入字符的位置
        for (auto& c : s) { // 遍历每个字符
            if (c == '*') { // 如果当前字符为*，则插入位置回退
                -- pos;
                continue;
            }
            res[pos] = c;   // 否则插入当前字符，并前进指针
            ++ pos;
        }
        return res.substr(0, pos);  // 返回从0到指针位置的子字符串，即为结果
    }
};