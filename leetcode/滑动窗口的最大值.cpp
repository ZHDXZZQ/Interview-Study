/*
    思路： 双端单调队列，时间On，空间On
    1. 利用双端队列维护窗口，存储下标，下标对应的值在队列中单调递减
    2. 这样对头下标对应的元素一定是当前窗口内的最大值
*/

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> res;
        deque<int> deq;
        for (int i = 0; i < n; ++ i) {
            if (deq.size() && deq.front() <= i - k) {   // 如果当前队头已经不在窗口范围内，队头出队
                deq.pop_front();    // 一定不会连续出两个队头，但是有可能一个都不出，因此不用while
            }
            while (deq.size() && nums[i] > nums[deq.back()]) {  // 如果当前新滑入的元素大于队尾对应元素
                deq.pop_back(); // 出队，直到插入后能满足单调递减
            }   // 无需考虑是否会影响出队了的元素，因为从现在开始往后，直到该元素滑出窗口，最大值都是他或者后来的更大值，因此出队的元素已经无用
            deq.push_back(i);   // 将当前元素下标入队，此时队列内的下标对应的元素是单调递减的
            if (i >= k - 1) {   // 如果当前元素已经够了一个窗口的量，每滑动一个元素，就可以得到一个当前窗口的最大值
                res.push_back(nums[deq.front()]);
            }
        }
        return res;
    }
};