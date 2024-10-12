/*
    思路： 翻转，时间On，空间O1，完美解法
*/
class Solution {
public:
    string LeftRotateString(string str, int n) {
        // write code here
        if (str.empty()) {
            return "";
        }
        int len = str.size();
        n %= len;   // 找到实际要翻转的位置，因为大于n的话，前n个部分是不用管的，相当于没动
        reverse(str.begin(), str.begin() + n);
        reverse(str.begin() + n, str.end());
        reverse(str.begin(), str.end());    // 分别翻转再整体翻转
        return str;
    }
};