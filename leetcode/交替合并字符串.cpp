/*
    思路： 模拟，时间Om+n，空间O1
    1. 一次插入每个单词的每个字符，直到有一个单词被用完
    2. 将没用完的单词剩余的部分补在后面即可
*/

class Solution {
public:
    string mergeAlternately(string word1, string word2) {
        string res;
        int m = word1.size();
        int n = word2.size();
        int i = 0, j = 0;
        while (i < m && j < n) {
            res.push_back(std::move(word1[i ++]));
            res.push_back(std::move(word2[j ++]));
        }
        if (i >= m) {
            while (j < n) {
                res += word2[j ++];
            }
        } else {
            while (i < m) {
                res += word1[i ++];
            }
        }
        return res;
    }
};