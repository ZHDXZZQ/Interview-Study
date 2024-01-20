// 思路： 哈希表记录，时间On，空间O1
// 1. 记录magazine中每个字母出现的次数
// 2. 判断是否能满足ransomNote中字母的需要

class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        unordered_map<char, int> usage;
        for(auto& c : magazine) {   //记录每个字符的数量
            ++ usage[c];
        }
        for(auto& c : ransomNote) {
            if(usage.find(c) == usage.end() || usage[c] <= 0) { //如果该字符不存在且剩余数量不足1，则失败
                return false;
            } else {    //否则，将剩余数量-1
                -- usage[c];
            }
        }
        return true;
    }
};