/*
    思路： 哈希，时间On，空间On
*/

class Solution {
public:
    bool isUnique(string astr) {
        unordered_set<char> uset;
        for (auto& c : astr) {
            if (uset.find(c) == uset.end()) {
                uset.insert(c);
            } else {
                return false;
            }
        }
        return true;
    }
};