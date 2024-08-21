// 题目：
// 给定一个数组，和一个目标值x，
// 每次可以从数组最左边或最右边的元素删除一个数字，将x减去删去的这个数字，
// 重复任意次上述操作，如果x可以减为0，则返回最少操作次数，否则返回-1。
// 数字都是非负整数

/*
    思路： dfs回溯，时间O2^n，空间On
    1. 每次都要对两边做尝试，然后回溯，每次都要计算到底
*/

// 优化：滑动窗口找区间前缀和即可

#include <deque>
#include <vector>
#include <iostream>

using namespace std;

const int INF = 1e9;
int res = INF;

void dfs(deque<int>& deq, int x, int cur_res) {
    if (x == 0) {   // 如果x为0，则找到了一个结果
        res = min(res, cur_res);    // 取操作最小值
    } else if (x < 0) { // 如果已经小于0，则不可能加回来，则返回
        return;
    }
    int l = deq.front();
    int r = deq.back();
    deq.pop_front();
    dfs(deq, x - l, cur_res + 1);   // 计算取左边的情况
    deq.push_front(l);              // 回溯
    deq.pop_back();
    dfs(deq, x - r, cur_res + 1);   // 计算取右边的情况
    deq.push_back(r);               // 回溯
    return ;
}

int main() {
    vector<int> nums = {1, 2, 3, 4, 5};
    int x = 6;
    deque<int> deq;
    for (auto& num : nums) {
        deq.push_back(num);
    }
    dfs(deq, x, 0);
    if (res == INF) {
        cout << -1;
    } else {
        cout << res;
    }
    return 0;
}