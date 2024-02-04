// 思路： 哈希表，时间On+m（两个串长度相同时直接为n），空间Os，最多需要26个字符的空间，可以算作O1
// 1. 先记录第一个串中所有字符的数量
// 2. 遍历第二个串，在哈希表中将第二个串中所有字符的数量减去
// 3. 遍历哈希表，如果所有字符的数量全为0，则匹配

class Solution {
public:
    bool isAnagram(string s, string t) {
        unordered_map<char, int> c_cnt;
        for (auto& c : s) {
            ++ c_cnt[c];
        }
        for (auto& c : t) {
            -- c_cnt[c];
        }
        for (auto& iter : c_cnt) {
            if(iter.second != 0) return false;
        }
        return true;
    }
};