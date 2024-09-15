/*
    思路： 双指针，区域移动，时间On²，空间O1
    也可以用时间On，空间On，先拿奇数再拿偶数两次遍历完成
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
    vector<int> reOrderArray(vector<int>& array) {
        // write code here
        int n = array.size();
        int even = 0;
        while (even < n && array[even] % 2 == 1) {
            ++ even;    // 找到第一个偶数，这之前都是奇数
        }
        int odd = even + 1; // 开始找偶数后的奇数
        while (odd < n) {
            if (array[odd] % 2 == 1) {  // 找到奇数
                int odd_num = array[odd];   // 记录下来
                for (int i = odd; i > even; -- i) { // 把偶数到奇数之间的数（全部都是偶数）往后移动
                    array[i] = array[i - 1];
                }
                array[even] = odd_num;  // 把奇数放到最前面
                ++ even;    // 记录第一个偶数的位置
            }   
            ++ odd; // 找奇数
        }
        return array;
    }
};