// 思路： 改造模拟，时间On，空间O1
// 1. 找规律发现，首尾行遍历的字符下标构成等差数列，首项为行号，差为2 * 行数 - 2
// 2. 中间行都由两个等差数列构成，首项分别为行号和2 * 行数 - 2 - 行号，差均为2 * 行数 - 2
// 3. 当行数为1时，需要特判，即原串。其余情况按规律模拟输出即可

class Solution {
public:
    string convert(string s, int numRows) {
        string res;
        if (numRows == 1) return s;  //特判，行数为1的话就是原串
        for (int cur_row = 0; cur_row < numRows; ++ cur_row) {   //cur_row代表当前遍历第几行
            if (cur_row == 0 || cur_row == numRows - 1) {        //第一行和最后一行间距是恒定的，两个字符间都是相隔2 * 行数 - 2，起始位置即为行号
                for (int pos = cur_row; pos < s.size(); pos += 2 * numRows - 2)     //pos为当前模拟遍历时所指的字符下标
                    res += s[pos];
            } else {            //中间的行由两组等差数列交替构成，差值相同和前面相同，起始位置不同
                for (int pos_first = cur_row, pos_second = 2 * numRows - 2 - cur_row; pos_first < s.size() || pos_second < s.size(); pos_first += 2 * numRows - 2, pos_second += 2 * numRows - 2) {
                    if (pos_first < s.size()) res += s[pos_first];    //pos_first为第一组等差数列
                    if (pos_second < s.size()) res += s[pos_second];  //pos_second为第二组等差数列
                }
            }
        }
        return res;
    }
};