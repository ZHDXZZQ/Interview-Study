// 思路： 快排、桶排、堆排皆可，时间快排/桶排On、堆排Onlogn；空间快排堆排Ologn，堆排On
// 这里先按桶排做，堆排和快排模版在八股中写
// 1. 桶排序，把每个数字当作一个桶，数字有多大就有多少个桶
// 2. 将所有数字装入桶中，然后按序从每个桶中把数字拿出，就会得到有序序列
// 3. 本题数字范围是-10000到10000，因此我们需要的桶数量为0-20000
// 4. 取第k大的树，其实就是取增序排列的倒数第k个数

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        vector<int>bucket(20001, 0);    //建立n个桶
        for (int i = 0; i < nums.size(); ++ i ) {
            ++ bucket[nums[i] + 10000]; //遍历每个数，把每个数放入对应的桶中
        }   //每个桶记录了其下标为值的数字的个数
        for (int i = 20000; i >= 0; -- i ) {    //从后往前依次取出桶中的数字
            k -= bucket[i];     //每次取出当前最大的几个数
            if (k <= 0) {       //如果本次取完发现k小于等于0，说明第k大的数就在这个桶中
                return i - 10000;   //返回下标对应的值，就是对应的数字
            }
        }
        return 0;
    }
};