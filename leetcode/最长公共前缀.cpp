// 思路： 纵向遍历全部字符串，时间Omn，空间O1
// 1. 从前往后选取第一个字符串的所有字母
// 2. 将选取的字母与其他字符串相同位置的字母进行比较
// 3. 如果相同，则给结果字符串加上该字母
// 4. 如果不同或者该位置已经超过某字符串的长度，则返回结果字符串

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string res;
        for(int i = 0; i < strs[0].size(); ++ i) {  //遍历第一个字符串你的每个字母
            char& c = strs[0][i];
            for(auto& str : strs) {         //每个位置的字母去遍历其他字符串相同位置的字母
                if(str[i] != c || i >= str.size()) {    //如果字母不同或者已经到某个字符串的结尾，则说明res就是最长公共前缀
                    return res;
                }
            }
            res += c;       //否则全部匹配则加上该字母到结果字符串中
        }
        return res;
    }
};