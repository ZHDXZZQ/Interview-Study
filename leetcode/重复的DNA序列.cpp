// 思路： 哈希表，时间On，空间On
// 1. 每次截取当前的10个基因，存入map中
// 2. 如果某个基因序列达到2，则记录一次

class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        unordered_map<string, int> dna;
        int n = s.size();
        if (n < 10) {   //如果基因序列少于10个，则直接返回
            return {};
        }
        vector<string> res;
        for (int i = 0; i <= n - 10; ++ i) {    //否则的话遍历所有的10个的组合
            string temp = s.substr(i, 10);  //记录当前的10个基因
            ++ dna[temp];       //记入map中
            if (dna[temp] == 2) {   //如果恰好有2个，则记录一次
                res.push_back(temp);
            }
        }
        return res;
    }
};