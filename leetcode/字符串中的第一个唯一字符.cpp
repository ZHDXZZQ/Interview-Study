// 思路： 哈希表的应用， 时间On，空间O1（最多26个字符）
// 1. 用一个哈希表，k存储字符，v存储其第一次出现的下标
// 2. 如果字符出现第二次或更多次，则把v更新为一个很大的数
// 3. 遍历所有映射，找到位置的最小值，则为目标答案
// 4. 如果全部都是很大的数，说明全部出现过多次，返回-1

class Solution {
public:
    int firstUniqChar(string s) {
        unordered_map<char, int> c_pos; //记录当前字符及其对应的首次出现的下标
        int len = s.size();
        for (int i = 0; i < len; ++ i) {  //遍历所有字符
            char& cur = s[i];
            if (c_pos.find(cur) == c_pos.end()) {   //如果当前字符未存储过，说明未出现过，记录其当前出现的位置
                c_pos[cur] = i;
            } else {    //如果当前字符已经记录过，说明不是第一次出现
                c_pos[cur] = len;   //将当前字符的位置更新为len，即字符串之外作为特殊标记
            }
        }
        int res = len; 
        for (auto& iter : c_pos) {  //遍历所有存储过的结果
            res = min(res, iter.second);    //res更新为每个字符位置的最小值
        }   //如果字符出现过多次，则其val为len，则不会更新
        if (res == len) { return -1; }  //如果发现res没有更新过，说明都出现过不止一次
        return res; //否则的话res就是第一个只出现一次的字符的位置
    }
};