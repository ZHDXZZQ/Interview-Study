/*
    思路： 模拟，时间On，空间O1
    1. 首先去除前导空格
    2. 判断是否有正负符号
    3. 计算整数，并判断是否超出int范围
*/

class Solution {
public:
    int myAtoi(string str) {
        int ptr = 0;
        int n = str.size();
        while (ptr < n && str[ptr] == ' ') {    // 排除前导空格
            ++ ptr;
        }
        int sf = 1;
        if (str[ptr] == '-') {  // 判断是否有符号
            sf = -1;
            ++ ptr;
        } else if (str[ptr] == '+') {
            ++ ptr;
        }
        long long res = 0;
        while (ptr < n && str[ptr] >= '0' && str[ptr] <= '9') { // 将数字部分计算出来
            res = res * 10 + str[ptr] - '0';
            ++ ptr;
            if (res >= pow(2, 31)) {    // 如果超过int范围，则停止并退出
                res = pow(2, 31);
                break;
            }
        }
        if (sf == -1) { // 如果为负，直接返回其相反数即可
            return -res;
        }
        if (res == pow(2, 31)) {    // 否则的话要考虑正数是否超过2的31次方-1，并返回
            return pow(2, 31) - 1;
        }
        return res;
    }
};