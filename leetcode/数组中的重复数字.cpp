/*
    思路： 特殊技巧，时间On，空间O1，最优解
    1. 因为数字一定不超过数组范围，因此我们把碰到的数字移动到其对应下标下
    2. 如果当前数字就是对应下标，不用管
    3. 如果对应下标的数字已经是正确的，那么当前数组和对应下标的数字冲突，有重复
    4. 否则交换到正确位置。
    解法二：排序查重，时间Onlogn，空间On
    解法三：哈希set，时间On，空间On
*/

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param numbers int整型vector 
     * @return int整型
     */
    int duplicate(vector<int>& numbers) {
        // write code here
        int n = numbers.size();
        for (int i = 0; i < n; ++ i) {
            int& num = numbers[i];  // 当前数字
            if (i == num) { // 如果当前数字和其下标对应，不处理
                continue;
            } else {    // 如果不对应，则找到其为下标的值
                if (numbers[num] == num) {  // 如果目标位置已经有正确的值，重复
                    return num;
                } else {
                    swap(numbers[num], numbers[i]); // 否则交换，将该数字放到目标位置
                }
            }
        }
        return -1;
    }
};