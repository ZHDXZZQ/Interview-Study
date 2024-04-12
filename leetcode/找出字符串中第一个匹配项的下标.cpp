// 思路： KMP算法， 时间Om+n，空间On，其中n为模式串的长度，m为主串的长度
// 1. 首先求next数组，利用KMP算法，可以保证主串指针不回退，只扫描一遍主串
// 2. next数组求法：前两位固定0 0，然后每一位为模式串中砍掉当前位的前面的字符串的最大匹配前后缀
// 3. 然后匹配的过程中，如果遇到二者不匹配的情况，直接将模式串指针调整到next所指的位置，可以避免前面重复的串被重复判断
// 4. 遇到第一个就不匹配的情况，主串指针前进一位
// 5. 具体的可以先去看一遍KMP的课程再来做这个题
// 6. 本题提前求解next数组的方法的复杂度为On^2，整体时间复杂度为Omax((m+n),n^2)

class Solution {
public:
    int strStr(string haystack, string needle) {
        int m = haystack.size();
        int n = needle.size();
        // 求next数组
        vector<int> next(n, 0); //求解next数组的方法可优化
        for (int i = 2; i < n; ++ i) {
            int max_len = i - 1;
            while (max_len > 0) {   //从可截取的最长往下截取
                string start = needle.substr(0, max_len);
                string end = needle.substr(i - max_len, max_len);
                if (start == end) { //最先相同的一次最最长前后缀
                    next[i] = max_len;
                    break;
                } else {            //否则本次结束，减少当前截取长度
                    -- max_len;
                }
            }
        }
        int i = 0, j = 0;   //i指向主串，j指向模式串，匹配
        while (i < m && j < n) {    //如果两个串有任意一个到头，匹配失败
            if (haystack[i] == needle[j]) { //如果当前字母一样
                ++ i;   //两个一起递增
                ++ j;
                if (j == n) {   //如果模式串匹配完毕，返回当前主串中该串的开头
                    return i - n;
                }
            } else {    //如果两个字符不一样
                if (j == 0) {   //如果此时是模式串的开头
                    ++ i;       //则直接另主串++
                } else {
                    j = next[j];    //否则另模式串指针跳转到next位置
                }
            }
        }
        return -1;
    }
};