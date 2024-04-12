// 思路： 模拟，时间On，空间On，n为所有字符串长度之和
// 1. 只需考虑两种情况，正常行，两端对齐即可
// 2. 中间某单词过长，只有一个单词，左端对齐补空格即可
// 3. 最后一行的几个单词，后边补空格即可

class Solution {
public:
    void full_res(int& maxWidth) {  //清空缓冲区
        int size = buf.size();
        if (size == 0) { return; }  //如果当前缓冲区为空，即没有最后一行单词，返回
        string cur_res;
        if (is_finish || size == 1) {   //如果是最后一行，或者只有一个超长的单词
            int empty_size = maxWidth - buf_len + size; //记算当前可插入的空格数
            for (auto& str : buf) { //遍历所有缓冲区的字符串
                cur_res += str;     //插入临时结果
                if (empty_size > 0) {   //此时每个单词后面只插入一个空格
                    cur_res += ' ';
                    -- empty_size;
                }
            }
            while (empty_size > 0) {    //将还剩余的空格补充到最后
                cur_res += ' ';
                -- empty_size;
            }
        } else {    //否则的话，就是正常插入
            int empty_size = maxWidth - buf_len + size; //计算能插入的空格数
            int extra = empty_size % (size - 1);    //计算左边单词可以多插入的空格数
            empty_size = empty_size / (size - 1);   //计算每个单词后可插入的空格数
            for (int i = 0; i < size; ++ i) {
                auto& str = buf[i];         //遍历每个单词
                cur_res += str;
                if (i == size - 1) { break; }    //如果是最后一个单词，不插入任何空格
                for (int t = 0; t < empty_size; ++ t) { //否则的话，每个单词后面先插入固定能插入的空格数
                    cur_res += ' ';
                }
                if (extra > 0) {    //再在左边的单词把能多插的空格数插入
                    cur_res += ' ';
                    -- extra;
                }
            }
        }
        res.push_back(cur_res); //将当前结果作为一行插入结果中
        buf.clear();    //清空缓冲区
        buf_len = 0;
    }

    vector<string> fullJustify(vector<string>& words, int& maxWidth) {
        int n = words.size();
        for (int i = 0; i < n; ) {  //遍历所有单词
            auto& str = words[i];
            int len = str.size() + 1;   //空格算作1个字符，因为每个单词后必须有一个空格，计算当前字符串长度
            buf_len += len;     //假设把该字符串加入缓冲区
            if (buf_len > maxWidth) {   //如果缓冲区长度超过
                if (buf_len == maxWidth + 1) {  //如果只超过一个，说明是该行最后一个单词的空格导致，无所谓
                    buf.push_back(str); //将该单词插入缓冲区
                    full_res(maxWidth); //将缓冲区写入结果
                } else {            //否则的话长度超过
                    buf_len -= len; //该单词不插入缓冲区
                    full_res(maxWidth); //将当前缓冲区写入结果
                    continue;       //不指向下一个单词，将当前字符串作为下一行的头一个单词
                }
            } else {    //如果长度没超过
                buf.push_back(str); //直接插入缓冲区
            }
            ++ i;   //指向下一个单词
        }
        is_finish = true;   //当前遍历完成，缓冲区内存储的是最后一行字符串
        full_res(maxWidth); //插入结果
        return res;
    }

protected:
    bool is_finish = false; //是否是最后一行
    vector<string> res; //结果
    int buf_len = 0;    //当前缓冲区内所有字符串的长度和
    vector<string> buf; //缓冲区，当前待添加的单词
};