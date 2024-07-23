/*
    思路： 滑动窗口模板题，时间On，空间On
    1. 利用单调队列存储当前窗口中最值得下标
*/

#include <iostream>
#include <deque>
#include <vector>

using namespace std;

int main() {
    deque<int> min_q;   // 存储当前窗口中最值的下标，队头的下标就是当前窗口中的最值，在窗口移动出前他都是最值，如果更更大或更小的值进入窗口，会将其挤出
    deque<int> max_q;   // 单调递减队列存储最大值下标，单调递增队列存储最小值下标
    int n, k;
    cin >> n >> k;
    vector<int> nums(n);    // 存储所有数字
    vector<int> res_min, res_max;   // 存储结果
    for (int i = 0; i < n; ++ i) {
        cin >> nums[i];
        if (i - max_q.front() >= k) {   // 如果队头已经滑出窗口，队头出队
            max_q.pop_front();
        }
        while (max_q.size() && nums[i] >= nums[max_q.back()]) { // 单调队列，新值如果大于等于队尾，则出队，这样队头维护的一定是最值，队头移出后，新的队头还是最值
            max_q.pop_back();
        }
        max_q.push_back(i); // 将比其小的值都出队后，前面的值一定就是更大的值，并且都在窗口内

        if (i - min_q.front() >= k) {   // 同理处理最小值队列，维护单调递增队列，队头一定是最大值下标
            min_q.pop_front();
        }
        while (min_q.size() && nums[i] <= nums[min_q.back()]) {
            min_q.pop_back();
        }
        min_q.push_back(i);
        if (i >= k - 1) {   // 当队列填满后，每次取出队头作为当前队列的最值
            res_min.push_back(nums[min_q.front()]);
            res_max.push_back(nums[max_q.front()]);
        }
    }
    for (auto& x : res_min) {
        cout << x << " ";
    }
    cout << endl;
    for (auto& x : res_max) {
        cout << x << " ";
    }
    return 0;
}