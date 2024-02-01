// 思路： 哈希表，时间Om+n，空间Om+n
// 1. 遍历pattern，同时找对应单词，将单词和字符的对应关系存到两个哈希表中
// 2. 如果内容不对应、或者pattern和单词的数量不对应，则错误
// 3. 否则正确

class Solution {
public:
    bool wordPattern(string pattern, string s) {
        unordered_map<char, string> dict;       //存字符对应单词
        unordered_map<string, char> reverse_dict;   //存单词对应字符
        int n = s.length();
        int ptr = 0;        //用于遍历s，找到每个单词
        for (auto& c : pattern) {   //遍历字符
            string word;
            if(ptr >= n) return false;      //如果ptr已经超过了s的大小，说明字符比单词多，返回错误
            while (ptr < n && s[ptr] != ' ') {  //否则ptr往后找，直到遍历完s或者碰到空格
                word += s[ptr];     //将每个字母插入word，组成单词
                ++ ptr;             //ptr后移
            }
            ++ ptr;                 //ptr后移，指向下个单词的首字母，不影响是否遍历完s
            if(dict.find(c) != dict.end()) {    //如果该字符存储过
                if(dict[c] != word) return false;   //看看单词是否对应，不对应则返回错误
            } else {
                dict[c] = word;     //如果没有存储过，则将该组合存入
            }
            if(reverse_dict.find(word) != reverse_dict.end()) { //如果该单词存储过
                if(reverse_dict[word] != c) return false;       //看看二者是否对应，不对应返回错误
            } else {
                reverse_dict[word] = c;     //否则将该单词对应的字符存入
            }
        }
        if(ptr < n) return false;       //如果遍历完字符发现ptr未到头，说明单词多于字符数，返回错误
        return true;        //全部判断完毕，正确
    }
};