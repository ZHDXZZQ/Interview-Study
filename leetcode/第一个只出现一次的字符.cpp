/*
    思路： 哈希表，时间On，空间On
*/

class Solution {
public:
    int FirstNotRepeatingChar(string str) {
        // write code here
        unordered_map<char, int> umap;
        for (const auto& c : str) {
            ++ umap[c];
        }
        for (int i = 0; i < str.size(); ++ i) {
            if (umap[str[i]] == 1) {
                return i;
            }
        }
        return -1;
    }
};