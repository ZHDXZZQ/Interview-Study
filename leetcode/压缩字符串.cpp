/*
    思路： 双指针，时间On，空间O1，时间超过100%
    1. 用读写指针确定当前读写的位置，写一定不会覆盖读
    2. 统计当前相同连续字符的数量
    3. 当碰到不一样的字符时，看看是1个还是多个连续
    4. 1个无需处理，多个需要把个数转换字符并存入
    5. 特殊判断结尾时的情况
*/

class Solution {
public:
    int compress(vector<char>& chars) {
        int n = chars.size();
        int char_cnt = 1;   // 当前连续字符的数量
        int write_ptr = 1;  // 当前写的位置
        for (int read_ptr = 1; read_ptr <= n; ++ read_ptr) {    // 从第2个字符开始读
            if (read_ptr < n && chars[read_ptr] == chars[read_ptr - 1]) {   // 如果此时没读完，并且还和前面的字符相同
                ++ char_cnt;    // 连续字符数量+1
            } else {    // 如果读完了，或者字符不同了
                if (char_cnt != 1) {    // 如果字符数量不为1
                    string num = to_string(char_cnt);   // 将数量转换为字符串，最大值为2000，常数级空间
                    for (auto& c : num) {   // 把每个数字写入
                        chars[write_ptr ++] = c;
                    }
                    char_cnt = 1;   // 清零连续字符数
                }   // 无论字符连续是1个还是多个，都写入下一个字符
                if (read_ptr < n) { // 读完了就不用写了
                    chars[write_ptr ++] = chars[read_ptr];
                }
            }
        }
        return write_ptr;   // 写指针永远指向下一次该写的位置，正好是已写的数量
    }
};