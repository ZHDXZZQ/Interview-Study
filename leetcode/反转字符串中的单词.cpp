// 思路： 先反转单词再反转整体，时间On，空间O1
// 1. 遍历字符串，剔除单词前的空格
// 2. 将每个单词反转，保留单词后的空格
// 3. 剔除字符串尾部的所有无用空格
// 4. 反转整个字符串，达到仅反转单词顺序的效果
// 5. reverse函数内部也是遍历字符串且不用额外空间，符合最优解，可以手动自己实现（找到居中点两两调换首尾）

class Solution {
public:
    string reverseWords(string s) {
        int ptr = 0;
        while(ptr < s.size()) {
            int start = ptr;            //ptr记录上一个单词结束的位置，start最终指向当前单词的开头位置
            while(start < s.size() && s[start] == ' ') {
                ++ start;               //排除单词前的空格,指向单词开头字母
            }                          
            if(start == s.size()) {     //如果此时已经超过s，表明是最后一个单词后面的空格，删除后面的所有空格即可
                s.erase(s.begin() + ptr - 1, s.end());
                break;
            }
            s.erase(s.begin() + ptr, s.begin() + start);    //删除单词前的空格
            start = ptr;                //start指向删除空格后的单词开头的字母
            int end = start;            //end用于记录单词的结尾位置
            while(end < s.size() && s[end] != ' ') {
                ++ end;
            }                           //end找到单词结尾的位置，如果是最后一个单词也适用
            reverse(s.begin() + start, s.begin() + end);  //反转当前单词
            ptr = end + 1;              //ptr指向当前单词结尾处的空格的下一个位置
        }
        reverse(s.begin(), s.end());    //反转整个字符串
        return s;
    }
};