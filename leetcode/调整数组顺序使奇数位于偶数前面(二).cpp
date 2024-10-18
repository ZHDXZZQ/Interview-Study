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
    vector<int> reOrderArrayTwo(vector<int>& array) {
        // write code here
        int n = array.size();
        int l = 0, r = n - 1;
        while (l < n && array[l] % 2 == 1) {    // l指向前面的第一个偶数，随时和后面的奇数做交换
            ++ l;
        }
        while (l < r) {
            if (array[r] % 2 == 1) {
                swap(array[r], array[l]);
                while (l < r && array[l] % 2 == 1) {
                    ++ l;
                }
            }
            -- r;
        }
        return array;
    }
};