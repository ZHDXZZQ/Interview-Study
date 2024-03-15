// 思路：翻转时判断，时间Ologn，该题情境下可以算作时间O1，空间O1
// 1. 本题解法较多，可以将数字变为字符串翻转作比较（rbegin或reverse）；也可以将数字翻转成一个新的数字作比较但是有可能超出int范围
// 2. 本题选择边翻转边判断的做法，以O1的时间复杂度且可保证不超出int范围

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) { return false; }    //负数不可能是回文数
        else if (x % 10 == 0 && x != 0) { return false; } //如果当前数尾部是0，那么必须头部也是0，除了0之外不可能存在此数，防止后面误判，如10
        int r_num = 0;                  //用于记录部分翻转后的值
        while (r_num < x) {              //只要翻转的部分还小于x，则继续反转
            r_num *= 10;                //翻转值留出个位
            r_num += (x % 10);          //翻转值加上当前x的个位
            x /= 10;                    //x除以10，取整数部分
        }
        bool res = (x == r_num) || (x == r_num / 10);   //此时翻转后的值要么等于x，要么是抛弃掉个位后等于x，否则不是回文数
        return res;
    }
};