/*
    思路： 双指针，时间On，空间O1
*/

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param array int整型vector 
     * @return int整型vector
     */
    vector<int> FindGreatestSumOfSubArray(vector<int>& array) {
        // write code here
        vector<int> res;
        int n = array.size();
        int l = 0, r = 0;   // 记录当前区间
        int sum = 0;    // 记录当前区间和
        int biggest = -1e9; // 记录最大值
        int res_l = -1, res_r = -1; // 记录最大和区间的左右端点
        while (r < n) {
            sum += array[r];
            if (sum >= biggest) {   // 因为取长度最大的区间，所以如果此时区间和大于等于最大和
                biggest = sum;  // 更新最大和和最大和的左右端点
                res_l = l;
                res_r = r;
            }
            while (sum < 0 && l <= r) { // 当为负数时，要移动左端点直到变成非负数
                sum -= array[l];
                ++ l;
            }
            ++ r;
        }
        for (int i = res_l; i <= res_r; ++ i) {
            res.push_back(array[i]);
        }
        return res;
    }
};