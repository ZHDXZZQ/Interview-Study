// 思路： 从中间往两边遍历，时间On²，空间O1
// 1. 对于回文串，有可能是奇数个字符，有可能是偶数个字符，所以分别判断
// 2. 遍历每个字符，从该字符往两边遍历，这样形成的是奇数个字符的串
// 3. 从该字符和该字符的下一个字符往两边遍历，这样形成的是偶数个字符的串
// 4. 依次找到当前字符左右延申的最大偶数回文串和奇数回文串，选择更大的那个更新答案

class Solution {
public:
    string longestPalindrome(string s) {
        string res;
        int n = s.size();
        for(int i = 0; i < n; ++ i) {                   //遍历每个字符，从每个字符向两边扩展
            int o_x = i, o_y = i + 1, j_x = i, j_y = i; //o表示偶数标记，j表示奇数标记

            while(o_x > 0 && o_y < n - 1 && s[o_x] == s[o_y]) { //如果左右没有越界且两边的字符相等
                -- o_x;                     //则向两边延申
                ++ o_y;
            }                       
            //此循环结束只有两种情况，第一种为有一边或两边到边界了，第二种就是遍历到的两个字符不相同了
            //无论哪种情况，都取得了以当前字符为中心的最大偶数回文串
            if(s[o_x] == s[o_y]) {  //如果此时两边界的字符还相同，说明是因为到边界停止的
                int cur_len = o_y - o_x + 1;    //计算当前所包含的字符
                if(cur_len > res.size()) {      //如果长度更长
                    res = s.substr(o_x, o_y - o_x + 1); //截取并更新答案
                }
            } else {            //如果此时两边界字符不同，则说明是第二种情况，此时，不包含两边界内的字符串还是回文串
                int cur_len = o_y - o_x - 1;    //计算两边界内的字符的长度
                if(cur_len > res.size()) {      //如果更长，则更新答案
                    res = s.substr(o_x + 1, o_y - o_x - 1); //截取不包含两边界
                }
            }

            //以下同上，只不过是奇数个字符的回文串
            while(j_x > 0 && j_y < n - 1 && s[j_x] == s[j_y]) {
                -- j_x;
                ++ j_y;
            }
            if(s[j_x] == s[j_y]) {
                int cur_len = j_y - j_x + 1;
                if(cur_len > res.size()) {
                    res = s.substr(j_x, j_y - j_x + 1);
                }
            } else {
                int cur_len = j_y - j_x - 1;
                if(cur_len > res.size()) {
                    res = s.substr(j_x + 1, j_y - j_x - 1);
                }
            }
        }
        return res;
    }
};