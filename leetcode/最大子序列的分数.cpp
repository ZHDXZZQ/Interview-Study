/*
    思路： 贪心堆，时间Onlogn，空间On
    1. 让nums2降序排序，先计算前k个，越往后计算，nums2的值一定是越来越小的
    2. 把nums2排序后的前k个下标对应的nums1的值插入小根堆，计算
    3. 往后遍历时，nums2一定是越来越小的，如果碰到nums1中比堆顶更大的，就把堆顶最小的拿出来，插入更大的，然后统计是否结果变大
    4. nums1中选中的一定都是更大的值，nums2每次计算一下是否结果变大
*/

class Solution {
public:
    long long maxScore(vector<int> &nums1, vector<int> &nums2, int k) {
        int n = nums1.size();
        vector<int> ids(n);
        iota(ids.begin(), ids.end(), 0);    // 初始化ids，值为从0到n-1
        // 根据nums2的值，对下标排序，不影响原数组的顺序
        ranges::sort(ids, [&](int i, int j) { return nums2[i] > nums2[j]; });   // 对nums2的下标进行降序排序

        priority_queue<int, vector<int>, greater<>> pq; // 优先队列小根堆
        long long sum = 0;
        for (int i = 0; i < k; i++) {
            sum += nums1[ids[i]];   // 记录前k个在nums2中的高价值的值下标在nums1中的值的和
            pq.push(nums1[ids[i]]); // 堆中插入价值，方便后面nums1更新，此时nums2选出的一定是最大的几个了
        }

        long long ans = sum * nums2[ids[k - 1]];    // 计算当前k个的结果，ids[k-1]为在第二个数组中前k个数中的最小值的下标
        for (int i = k; i < n; i++) {   // 继续往后遍历
            int x = nums1[ids[i]];  // x为nums2中当前最小的数对应的nums1的值
            if (x > pq.top()) { // x的价值大于nums1前面的最小值
                sum += x - pq.top();    // 将这个值加入群组中，拿出之前的最小值。对于nums2变小的情况来说，nums1的和一定是越大越好，所以可以直接插入更大的值
                pq.pop();
                pq.push(x); // 总是更新nums1中更大的数
                ans = max(ans, sum * nums2[ids[i]]);    // 更新答案，有点贪心的思想，nums1的数总是选取更大的，然后跟当前最小下标算一下是否总分更大
            }   // 如果nums1变小，而nums2是肯定变小的，那就没必要比较了。nums1变大，nums2变小还可以试试是否真的变大了
        }
        return ans;
    }
};