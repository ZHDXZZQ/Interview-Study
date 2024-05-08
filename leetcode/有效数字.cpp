/*
    思路： 有限状态机，时间On，空间O1
    1. 本题类型不建议大家死磕，属于面向用例编程，没啥意思
    2. 这里建议大家学学力扣官解的有限状态机，大家可以学学有限状态机的思路，但是这个题可以跳过
    3. 正常你没一个小时做不出来
*/
class Solution {
public:
    // 判断是否是个数
    bool is_num(string& s, int& ptr, bool e, bool point, bool space, bool end) {
        int n = s.size();
        int start = ptr;
        if (end && ptr == n) {  // 判断是否可以直接结束
            return true;
        }
        while (ptr < n) {
            if (s[ptr] >= '0' && s[ptr] <='9') {    // 判断是否是数字
                ++ ptr;
            } else {
                if (e && s[ptr] == 'e' || s[ptr] == 'E') {  // 判断是否可以以e结尾
                    if (ptr == 0 || ptr == 1 && (s[0] == '.' || s[0] == ' ' || s[0] == '+' || s[0] == '-')) {
                        return false;   // e 的前面一定是整数或小数
                    }
                    return true;
                } else if (point && s[ptr] == '.') {    // 判断是否可以以点结尾
                    return true;
                } else if (space && s[ptr] == ' ') {    // 判断是否可以以空格结尾
                    while (ptr < n && s[ptr] == ' ') {
                        ++ ptr;
                    }
                    if (ptr == n) { // 空格后不能有东西
                        return true;
                    }
                    return false;
                }
                return false;
            }
        }
        if (ptr != start) { // 判断是否啥也没有
            return true;
        }
        return false;
    }

    // 判断是否是个整数
    bool is_inte(string& s, int& ptr, bool e) {
        int n = s.size();
        if (ptr < n && s[ptr] == '+' || s[ptr] == '-') {    // 去除符号
            ++ ptr;
            if (ptr == n) { // 如果只有符号，错
                return false;
            }
        }
        return is_num(s, ptr, e, false, true, true);    // 判断是否是个数字
    }

    // 判断是否是个小数
    bool is_deci(string& s, int& ptr) {
        int n = s.size();
        if (ptr < n && s[ptr] == '+' || s[ptr] == '-') {    // 去除符号
            ++ ptr;
            if (ptr == n) { // 如果只有符号，错
                return false;
            }
        }
        if (s[ptr] == '.') {    // 如果第一个是点
            ++ ptr;
            if (ptr == n) {
                return false;
            } else if (s[ptr] == ' ') {
                return false;
            }
            if(!is_num(s, ptr, true, false, true, true)) {  // 则后面应该是数字
                return false;
            }
            return true;
        }
        if (!is_num(s, ptr, false, true, false, false)) {   // 如果第一个不是点，则应该是个数字
            return false;
        }
        if (s[ptr] == '.') {    // 数字后应该有点
            ++ ptr;
        }
        return is_num(s, ptr, true, false, true, true); // 判断点后是否是数字
    }

    bool validNumber(string s) {
        int ptr = 0;
        int n = s.size();
        while (ptr < n && s[ptr] == ' ') {  // 跳过前导空格
            ++ ptr;
        }
        if (ptr == n) {     // 如果全是空格，返回false
            return false;
        }
        int start = ptr;
        bool deci = is_deci(s, ptr);    // 判断是否是小数
        if (!deci) {        // 如果不是小数，指针归位，再判断是否是整数
            ptr = start;
        }
        if (!deci && !is_inte(s, ptr, true)) {  // 判断是否是整数
            return false;
        }
        if (s[ptr] == 'e' || s[ptr] == 'E') {   // 判断是否是指数
            ++ ptr;             // 跳过e或E
            if (ptr == n) { // 如果e后面没东西，错
                return false;
            } else if (s[ptr] == ' ') {
                return false;
            }
            if (!is_inte(s, ptr, false)) {  // 如果e后面不是整数，错
                return false;
            }
        }
        return true;
    }
};