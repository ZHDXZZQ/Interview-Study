// 思路： 模拟电路， 时间On，空间O1
// 1. 对于所有数字，利用一个拷贝的数字来记录每个位出现了几次
// 2. 对于二进制的任一位，如果他出现了3次，则变为0。就算多个数字都有这一位，出现三次的话也会变为0
// 3. 只有出现1次的情况会变为1，所以最后剩下的1就是出现一次的数字
// 4. 举例，利用一个额外的数字帮忙记录该位的情况，比如某一位出现了一次，我们就在两个数字中对该位记录为0 1
// 5. 如果出现了两次，就记为1 0，如果出现了3次，就记录为0 0，即为0次，就好像从来没出现过
// 6. 具体的转化逻辑：假设原始我们存为one，辅助变量记为two，那么对于某一位为1的数字出现三次。
// 7. 出现前，二者为0 0，出现一次后变为0 1，再出现一次变为1 0，再出现一次变为0 0，如果碰到其他数字该位为0的情况，则不变
// 8. 相当于利用了逻辑门电路来实现记录原理

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int one = 0, two = 0;
        for (int& num : nums) {
            two = ~one & (two ^ num);   //这玩意儿确实不好想，建议直接拿哈希表秒了
            one = ~two & (one ^ num);   
        }
        return two;
    }
};


// 好想的写法
// 思路：上述方法的详细实现，时间O32n，空间O1
// 1. 记录的两位的格式为two， one
// 2. ～为全部取反，因为考虑负数的问题可能会使得pow不符合int范围，全部用long long类型实现

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        long long one = 0;
        long long two = 0;
        for (long long num : nums) {
            for (int i = 31; i >= 0; -- i) {
                long long cur_one = (one >> i) & 1;
                long long cur_two = (two >> i) & 1;
                long long cur = (num >> i) & 1;
                if (cur_one == 0 && cur_two == 0) {
                    if (cur == 1) {//0 0变成0 1
                        long long  sum = pow(2, i);
                        cur_one = sum;
                        one |= cur_one; //其余位不变，本位变1
                    }
                } else if (cur_one == 0 && cur_two == 1) {
                    if (cur == 1) { //1 0变成0 0
                        long long sum = pow(2, i);
                        cur_two = ~sum;
                        two &= cur_two; //其余位不变，本位变0
                    }
                } else if (cur_one == 1 && cur_two == 0) {
                    if (cur == 1) { //0 1变成1 0
                        long long sum = pow(2, i);
                        cur_one = ~sum; 
                        one &= cur_one; //其余位不变，本位变0
                        cur_two = sum;
                        two |= cur_two; //其余位不变，本位变1
                    }
                }
            }
        }
        return int(one);    //one存储的就是最终结果
    }
};