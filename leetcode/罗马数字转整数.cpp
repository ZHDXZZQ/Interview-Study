// 思路： 利用哈希表，时间On，空间O1
// 1. 先用umap存储每个字符及其对应的数字
// 2. 利用题目中罗马数字的特性，即小的数字一般在大的数字的右边
// 3. 如果右边的数字更大，则要减去当前这个小的数字，否则就加上

class Solution {
public:
    unordered_map<char, int> sti = { //存储每个字符对应的数字
        {'I', 1}, 
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000}
    };

    int romanToInt(string s) {
        int res = 0;
        for(int i = 0; i < s.size(); ++ i) { //遍历整个字符串
            if(i < s.size() - 1 && sti[s[i]] < sti[s[i + 1]]) {     //如果当前字符右边还有字符且小于右边的字符，说明是要减去
                res -= sti[s[i]];
            } else {
                res += sti[s[i]];       //如果是最后一个字符或者是右边的字符大于等于当前字符，说明是要加上
            }
        }
        return res;
    }
};