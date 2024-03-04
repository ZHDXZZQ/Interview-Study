// 左右边界两个指针当作窗口
// 如果当前窗口超过n，去除左边的值
// 如果当前窗口的和为负数，去除左边的值直到为正
// 如果当前左边的值为负数，则去除，直到左边的值为正
// 左边界不可以超过右边界

// 用例有些没过，请教下各位哪里有问题？

class Solution {
public:
    int res = INT_MIN;
    int cur_res = 0;
    int left = 0, right = 0;
    int n = 0;

    void del_left(vector<int>& nums) {
        cur_res -= nums[left % n];
        ++ left;
        if(left != right) {
            res = max(res, cur_res);
        }
        return;
    }

    int maxSubarraySumCircular(vector<int>& nums) {
        n = nums.size();
        while(right < 2 * n) {
            while(left < right && (nums[left % n] <= 0 || cur_res <= 0 || right - left >= n)) {
                del_left(nums);
                cout << "t1 : " << "left = " << left << " , right = " << right << " , cur res = " << cur_res << " , res = " << res << endl; 
            }
            cur_res += nums[right % n];
            ++ right;
            res = max(res, cur_res);
            cout << "t2 : " << "left = " << left << " , right = " << right << " , cur res = " << cur_res << " , res = " << res << endl; 
        }
        return res;
    }
};