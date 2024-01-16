// 思路： 双指针法，时间On，空间O1
// 1. 指针分别指向头尾
// 2. 二者向中间靠拢，跳过非有效字符，仅判断有效字符是否相同
// 3. 如果有不同的，则认为不是回文串。否则如果二者指针相遇，说明回文

class Solution {
public:
    bool check(char& c) {  //判断当前字符是否有效
        if(c >= '0' && c <= '9' || c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') {
            return false;
        }
        else return true;
    }

    bool isPalindrome(string s) {
        int l = 0;
        int r = s.size() - 1;
        while(l < r) {
            while(l < r && check(s[l])) {  //当两个指针还未遇到，且某一指针所指字符无效时，调整指针
                ++ l;
            }
            while(l < r && check(s[r])) {
                -- r;
            }
            if(l < r) {  //调整后如果仍未遇到，开始判断
                if(s[l] != s[r]) {  //如果二者字符不同，且任一为数字，则说明真的不同，不是回文的
                    if(s[l] >= '0' && s[l] <= '9' || s[r] >= '0' && s[r] <= '9') {
                        return false;
                    } else if(s[l] != s[r] + 32 && s[l] != s[r] - 32) {  //如果二者不同切都不是数字，则判断是否是同一个字母的大小写
                        return false;
                    }
                }  //当判断二者相同时，调整指针位置
                ++ l;
                -- r;
            }
        }
        return true;
    }
};