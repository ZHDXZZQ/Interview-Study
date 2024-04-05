//思路： 滑动窗口， 时间Onm，其中n为s的长度，m为words中单个单词的长度；空间Omk，其中k为words中单词的个数
// 1. 使用哈希表统计每个单词的个数，并用来判断
// 2. 因为单词长度固定，所以我们将窗口的单位设计为一个单词的长度
// 3. 每次进出一个单词，这样只需要循环单词长度的次数即可

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int n = s.size();       //s的长度
        int cnt = words.size(); //单词个数
        int len = words[0].size();  //单词长度
        unordered_map<string, int> word_map;    //统计每个单词出现的次数
        vector<int> res;
        for (auto& word : words) {
            ++ word_map[word];
        }
        for (int i = 0; i < len; ++ i) {    //只需要遍历单词长度次即可，因为到达第二个单词的时候，在第一遍已经滑动窗口判断过了
            unordered_map<string, int> window;  //记录当前窗口内的单词和次数
            int match_cnt = 0;      //匹配的单词数量
            for (int j = i; j <= n - len; j += len) {   //j用来记录每个窗口内的当前的新进入的单词的开头下标
                if (j >= i + cnt * len) {       //如果j超过了当前窗口的最大单词个数，即words的单词数，那么要从窗口滑出前面的一个单词
                    auto word = s.substr(j - cnt * len, len);   //取出最前面的单词
                    -- window[word];
                    if (window[word] < word_map[word]) {    //如果这个单词取出后，导致窗口内该单词的数量小于预期
                        -- match_cnt;   //则取出了一个匹配的单词
                    }
                }
                auto word = s.substr(j, len);   //截取每个单词
                ++ window[word];                //加入窗口
                if (window[word] <= word_map[word]) {   //如果当前单词符合预期要求数
                    ++ match_cnt;       //匹配单词数+1
                }
                if (match_cnt == cnt) { //如果当前窗口的匹配数和总个数相等
                    res.push_back(j - len * (cnt - 1)); //将当前窗口的头下标插入结果
                    //j此时为窗口中最后一个单词的开头下标，因此减去总个数-1个单词的长度为当前窗口的开头的下标
                }
            }
        }
        return res;
    }
};

// 思路： 暴力解法会超时， 时间Onm，其中n为s的长度，m为需要单词的个数，空间On。理论上不应该超时。
// 具体看注释
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        unordered_map<string, int> word_map;    //记录有哪些单词，以及重复单词出现的次数
        int len = words[0].size();  //记录但个单词的长度
        int cnt = words.size();     //记录单词个数
        for (auto& word : words) {
            ++ word_map[word];
        }
        auto tmp_map = word_map;    //拷贝一份map
        int n = s.size();
        vector<int> res;
        for (int i = 0; i <= n - len * cnt; ++ i) { //遍历每个字符
            string cur_str = s.substr(i, len * cnt);    //从每个字符往后取words中所有单词长度和作为子串
            int ptr = 0;        //遍历当前子串
            for (int j = 0; j < cnt; ++ j) {
                string cur_word = cur_str.substr(ptr, len); //拿到每个单词
                if (word_map.find(cur_word) == word_map.end()) {    //如果单词不在目标中，结束
                    break;
                } else {
                    if (word_map[cur_word] > 0) {   //如果在目标中且数量合适，则匹配一个
                        -- word_map[cur_word];
                    } else {        //否则数量不合适，结束
                        break;
                    }
                }
                ptr += len;     //更新指针
            }
            int count = 0;
            for (auto& iter : word_map) {   //如果当前子串结束后每个单词都为0
                if (iter.second == 0) {
                    ++ count;
                }
            }
            if (count == tmp_map.size()) {  //这个子串的开头算作一个答案
                res.push_back(i);
            }
            word_map = tmp_map;             //重置map开启下一轮
        }
        return res;
    }
};