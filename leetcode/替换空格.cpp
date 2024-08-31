/*
    思路： 双指针，时间On，空间O1
    1. 先预算空格数量，扩充原串的空间
    2. 双指针法从新空间的末尾和原串末尾向前遍历，碰到空格做填充
*/

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param s string字符串 
     * @return string字符串
     */
    string replaceSpace(string s) {
        // write code here
        int cnt = 0;
        int n = s.size();
        for (auto& c : s) {
            if (c == ' ') {
                ++ cnt;
            }
        }
        int origin_tail = n - 1;    // 原串结尾字符
        int new_len = n + cnt * 2;  // 结果串长度
        int new_tail = n + cnt * 2 - 1; // 结果串结尾位置
        s.resize(new_len);  // 要resize，不能reserve

        for (int i = origin_tail, j = new_tail; i >= 0; -- i) {
            if (s[i] == ' ') {  // 原串如果是空格
                s[j --] = '0';  // 添加%20
                s[j --] = '2';
                s[j --] = '%';
            } else {
                s[j --] = s[i]; // 否则直接填过来
            }
        }


        return s;
    }
};