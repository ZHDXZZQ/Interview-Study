// 题目：每次可以跳1阶，2阶……n阶，问跳到n阶一共有多少种跳法，要求时间O1，空间O1
// 思路：数学思维
// 1. 对于正常的跳台阶，可以采用动态规划
// 2. 对于本题，每个台阶都可以从上1，2，3……m-1跳过来，也就是所有到达前面台阶的跳法的和
// 3. 因此不难算出有2的n-1次方种方法到达这个台阶

#include <math>
class Solution {
public:
    int tiaotaijie (int number) {
        return pow(2, number - 1);
    }
};