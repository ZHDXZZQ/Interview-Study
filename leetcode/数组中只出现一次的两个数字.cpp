/*
    思路： 位运算，时间On，空间O1
    1. 利用异或，每组相同的两个数字，结果都是0
    2. 目标的两个数字异或一定不为0，利用这两个数字异或的结果的位为1的位，进行分组
    3. 无论两边分组的数量多少，各自分组后异或，两边剩下的一定就是两个目标数
*/

class Solution {
public:
    vector<int> FindNumsAppearOnce(vector<int>& nums) {
        // write code here
        // 先将全部数进行异或运算，得出最终结果
        int tmp = 0;
        for (int& num : nums) {
            tmp ^= num;
        }
 
        // 找到那个可以充当分组去进行与运算的数
        // 从最低位开始找起
        int mask = 1;
        while ((tmp & mask) == 0) {
            mask <<= 1;
        }
 
        // 进行分组，分成两组，转换为两组 求出现一次的数字 去求
        int a = 0;
        int b = 0;
        for (int& num : nums){
            if ((num & mask) == 0) {
                a ^= num;
            } else {
                b ^= num;
            }
        }
        // 因为题目要求小的数放前面，所以这一做个判断
        if (a > b) {
            int c = a;
            a = b;
            b = c;
        }
        return {a, b};
    }
};