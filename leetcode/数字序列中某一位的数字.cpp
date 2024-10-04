/*
    思路： 位数减法，时间Olgn，空间O1
    第n个数，0是第0个数
    1-9一共9个个位数，10-99一共90个两位数，100-999一共900个三位数
    以此类推，1000-9999一共90000个四位数
    根据这个规律找到目标位置所处的区间，根据区间内数字的位数weishu来确定具体数字
*/

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param n int整型 
     * @return int整型
     */
    typedef long long LL;
    int findNthDigit(int n) {
        // write code here
        int weishu = 1; // 记录当前区间的数字的位数
        LL start = 1;   // 记录当前区间的该位数的数字的第一个数字，比如1， 10， 100， 1000....
        LL sum = 9;     // 记录当前区间及之前的数字的位数总和
        while (n > sum) {   // 如果n超过这个区间
            n -= sum;   // n减去当前区间
            start *= 10;    // 进入下一个区间
            ++ weishu;      // 位数同步+1
            sum = 9 * start * weishu;   // 记录新区间的所有数字的位数之和
        }
        int num = start + (n - 1) / weishu; // 找到目标位所在的数字
        string res = to_string(num);
        int index = (n - 1) % weishu;   // 找到目标位所在的数字中的下标
        return res[index] - '0';
    }
};