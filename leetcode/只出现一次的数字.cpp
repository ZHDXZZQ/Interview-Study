// 思路： 位运算，时间On，空间O1
// 1. 异或运算的规律是0异或1得1，其余得0
// 2. 因此，两个相同得数的二进制是相同的，他们异或后全部为0
// 3. 所以将所有数进行异或，最后留下的为1的二进制数就是那个单独的数的二进制表示。其余的两两抵消

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0;
        for(auto x : nums) res = res ^ x;  //异或，两个二进制相同就是0，不同的就是1
        return res;
    }
};