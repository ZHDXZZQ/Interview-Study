// 思路：哈希映射，双向映射。时间On，空间O（字符的个数，最大为26，可以认为O1？）
// 1. 用一个char对char的map，存储s的每个字符对应的t中的字符
// 2. 用一个char的set，存储已经被对应过的t中的字符
// 3. 遍历s和t，每个对应的字符对去判断是否存储在umap中，如果已经存在，判断是否相同。如果不同，则失败
// 4. 如果不存在，插入这对字符。插入时需判断t中的字符是否已有对应的s中的字符
// 5. 如果不存在，则正常插入。如果存在，则失败

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        int n = s.size();
        unordered_map<char, char> char_hash_map;
        unordered_set<char> used_char_uset;
        for(int i = 0; i < n; ++ i) {
            char& c = s[i];
            if(char_hash_map.find(c) == char_hash_map.end()) {
                char_hash_map[c] = t[i];
                if(used_char_uset.find(t[i]) == used_char_uset.end()) {
                    used_char_uset.insert(t[i]);
                } else return false;
            } else {
                if(t[i] != char_hash_map[c]) {
                    return false;
                }
            }
        }
        return true;
    }
};