/*
    思路： 哈希表记录，时间Onlogn，空间On
    1. 对于操作1，只要两个字符串的字符种类及其数量一致，那么通过调序，一定可以转换
    2. 对于操作2，只要两个字符串的各字符的出现次数的集合相同，则通过转换，一定可以使得各字符个数一致
    3. 此时，如果字符种类也一致，那么通过操作1即可实现转换，否则无法实现
*/

class Solution {
public:
    bool closeStrings(string word1, string word2) {
        if (word1.size() != word2.size()) { // 如果字符串大小不同，直接失败
            return false;
        }
        unordered_map<char, int> umap1, umap2;
        for (auto& c : word1) { // 统计两个字符串中各字符的数量
            ++ umap1[c];
        }
        for (auto& c : word2) {
            ++ umap2[c];
        }
        string w1_chars, w2_chars;  // 记录两个字符串中各字符的种类
        vector<int> w1_char_cnt, w2_char_cnt;   // 记录两个字符串中各字符出现的数量的集合
        for (auto& it : umap1) {
            w1_chars += it.first;
            w1_char_cnt.push_back(it.second);
        }
        for (auto& it : umap2) {
            w2_chars += it.first;
            w2_char_cnt.emplace_back(it.second);
        }
        sort(w1_char_cnt.begin(), w1_char_cnt.end());   // 都按序排好
        sort(w2_char_cnt.begin(), w2_char_cnt.end());
        sort(w2_chars.begin(), w2_chars.end());
        sort(w1_chars.begin(), w1_chars.end());
        if (w1_char_cnt == w2_char_cnt && w2_chars == w1_chars) {   // 如果种类一致且数量集合一致，那么通过操作2再经过操作1一定可以实现转换
            return true;
        }
        return false;
    }
};