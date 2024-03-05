// 完美解法：
// 思路： 具体思路如下，时间On，空间O1
// 1. 第一种情况是最大子数组和就在该数组中连续，不涉及环状的头尾相接空中间的情况，则类似前面的53题最大子数组和
// 2. 第二种情况就是最大子数组和是首尾各一部分，在数组中看不是连续的，而中间这部分就是单个数组中的最小子数组和
// 3. 整个数组的和减去最小的子数组的和，其值和最大子数组和选最大，一定就是最大的子数组的和
// 4. 所以只需要计算最大子数组和、最小子数组和然后计算即可

class Solution {
public:
    int maxSubarraySumCircular(vector<int>& A) {
        int total = 0;                   // 数组的总和
        int maxSum = A[0];               // 最大子数组和的初始值为第一个元素
        int curMax = 0;                  // 当前子数组和的最大值
        int minSum = A[0];               // 最小子数组和的初始值为第一个元素
        int curMin = 0;                  // 当前子数组和的最小值

        // 遍历数组中的每一个元素
        for (int& a : A) {
            curMax = max(curMax + a, a);             // 更新当前子数组和的最大值
            maxSum = max(maxSum, curMax);            // 更新最大子数组和的值
            curMin = min(curMin + a, a);             // 更新当前子数组和的最小值
            minSum = min(minSum, curMin);            // 更新最小子数组和的值
            total += a;                              // 计算数组的总和
        }

        // 如果最大子数组和大于零，则返回最大子数组和和 (总和 - 最小子数组和) 中的较大值；否则，返回最大子数组和本身
        return maxSum > 0 ? max(maxSum, total - minSum) : maxSum;
        // 如果最大子数组和小于0，则表明其实表中全为负数，则maxSum记录的其实是最大的数
        // 如果为正数，则表明他可能是第一种情况也可能是第二种情况，则利用max判断选最大即可
        // 为什么要用max，因为这个最大子数组和最小子数组可能并不能沾满整个的数组，因此不能单纯的用总和减最小子数组和来计算
    }
};




// 解法2：
// 思路：模拟滑动窗口解法，破环成链。时间On，空间O1
// 左右边界两个指针当作窗口
// 如果当前窗口超过n，去除左边的值
// 如果当前窗口的和为负数，去除左边的值直到为正
// 如果当前左边的值为负数，则去除，直到左边的值为正
// 左边界不可以超过右边界

// 用例有些没过，请教下各位哪里有问题？

class Solution {
public:
    int res = INT_MIN;  //最终结果
    int cur_res = 0;    //当前窗口和
    int left = 0, right = 0;    //窗口边界
    int n = 0;  //数组长度

    void del_left(vector<int>& nums) {  //删除左端点
        cur_res -= nums[left % n];
        ++ left;
        if(left != right) {
            res = max(res, cur_res);
        }
        return;
    }

    int maxSubarraySumCircular(vector<int>& nums) {
        n = nums.size();
        while(right < 2 * n) {  //2n代表整个圆环变成的链
            while(left < right && (nums[left % n] <= 0 || cur_res <= 0 || right - left >= n)) {
                del_left(nums);
            }
            cur_res += nums[right % n];
            ++ right;
            res = max(res, cur_res);
        }
        while(left != right) {
            del_left(nums);
        }
        
        return res;
    }
};