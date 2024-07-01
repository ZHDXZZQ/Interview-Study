/*
    思路：简单二分，时间Ologn，空间O1
    1. 循环调用目标接口，判断当前中间值的大小关系，调整当前判断的值
*/

/** 
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is higher than the picked number
 *			      1 if num is lower than the picked number
 *               otherwise return 0
 * int guess(int num);
 */

class Solution {
public:
    int guessNumber(int n) {
        long long l = 1, r = n; // 用LL存储
        long long num = (l + r) / 2;
        int res = guess(static_cast<int>(num)); // 使用C++风格的类型转换
        while (res != 0) {  // 如果没有猜对，就一直猜
            if (res == -1) {    // 如果猜大了，则缩小区间
                r = num - 1;
            } else {    // 如果猜小了，也缩小区间
                l = num + 1;
            }
            num = l + r >> 1;   // 计算当前区间的中间数，用它来猜
            res = guess(int(num));  // 计算本次猜测结果
        }
        return num;
    }
};