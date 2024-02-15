// 思路： 排序后哈希，时间Onklogk，空间Onk，其中n为单词数目，k为单词长度
// 1. 将字母异位词排序后，所有异位词就会得到相同的结果，将这个结果作为索引
// 2. 将所有异位词存到哈希表的同一个索引下，最后插入结果即可

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> res;
        unordered_map<string, vector<string>> str_map;
        for(auto& str : strs) {     //遍历所有字符串
            auto tmp = str;
            sort(str.begin(), str.end());   //将字符串进行排序，异位词的顺序就会变成一致
            str_map[str].push_back(tmp);    //然后根据排序后的字符串将当前字符串插入对应分组中
        }
        for(auto& iter : str_map) res.push_back(iter.second);   //将每个分组内的单词组插入结果中
        return res;
    }
};