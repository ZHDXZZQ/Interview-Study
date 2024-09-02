/*
    思路： OS的短作业优先，时间Onlogn，空间On
    1. 同等待人数的情况下，做的人越快，等待的时间总和越少
    2. 所以先让速度快的人做，其他剩余的人等待他做的时间
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using LL = long long;

int main() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; ++ i) {
        cin >> nums[i];
    }
    sort(nums.begin(), nums.end());
    LL res = 0;
    for (int i = 0; i < n; ++ i) {
        res += nums[i] * (n - i - 1);
    }
    cout << res;
    return 0;
}