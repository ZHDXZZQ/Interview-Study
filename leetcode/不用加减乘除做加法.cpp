/*
    思路： 位运算，时间On，空间O1
*/

class Solution {
public:
    int Add(int num1, int num2) {
        while (num2 != 0) {
            int temp = num1 ^ num2;  //异或相当于各位相加，不考虑进位
            num2 = num1 & num2;
            num2 = num2 << 1;        //与运算左移一位就来搞定进位问题
            num1 = temp;            //num1和num2一直进行，直到num2=0就是处理了进位问题
        }
        return num1;
    }
};