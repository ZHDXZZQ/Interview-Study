/*
    思路： 动态规划，时间On²，空间On
    1. 利用dp数组记录从1-i中的最长子序列
    2. 每次遍历所有数字去判断，如果更大，则在其基础上+1
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    int dp[n];
    int nums[n];
    for (int i = 0; i < n; ++ i) {
        cin >> nums[i];
    }
    for (int i = 0; i < n; ++ i) {
        dp[i] = 1;      // 对于只有一个数时的情况，初始化为1
        for (int j = 0; j < i; ++ j) {  // 遍历前面的数字
            if (nums[i] > nums[j]) {    // 如果当前的数字大，则在上一个数的最长基础上+1
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    int res = 0;
    for (int i = 0; i < n; ++ i) {
        res = max(res, dp[i]);
    }
    cout << res;
    return 0;
}

/*
    思路： 动态规划+二分，时间Onlogn，空间On
    1. 要找最长的递增子序列，那么每碰到一个数，就要在不改变前面结果的情况下将他尽可能的插入序列中
    2. 举个例子，加入目前的序列是10， 9， 11， 2， 4， 7。 那么9和11是一个递增子序列，但是2 4 7才是最长的。
    3. 因此我们在更新递增子序列的同时，不是一味的往后加，而是往中间改，这样保证有更大的加到了结尾，有小于结尾的也插入到了合适位置并且不改变当前情况的合理性，还方便后面的介于二者之间的数字可以进入计算
    4. 模拟一下上述例子，先插入10，然后9更新掉10，然后11插入，当前是9 11，如果按只插入来算，后面的2 4 7都无法插入，也不方便再去开一个数组（时间复杂度会变成平方），因此我们2 4 7要更新
    5. 2更新掉9,4更新掉11,7再插入，就可以完美符合答案，保证了只增不减，且不会出现乱序情况
*/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> nums(n);
    vector<int> help_vec;
    for (int i = 0; i < n; ++ i) {
        cin >> nums[i];
    }
    for (int i = 0; i < n; ++ i) {
        if (help_vec.empty() || nums[i] > help_vec.back()) { help_vec.push_back(nums[i]); } //如果待插入数字大于数组末尾，则直接插入
        else {
            int l = 0, r = help_vec.size() - 1;     //否则的话要看看需要更新哪个位置
            while (l < r) {                     //二分找到待插入位置，这个插入位置的前一个数小于该数，后一个数大于该数，或者更新末尾
                int mid = (l + r) / 2;
                if (help_vec[mid] >= nums[i]) {
                    r = mid;
                } else {
                    l = mid + 1;
                }
            }
            help_vec[r] = nums[i];              //更新该位置
        }
    }
    cout << help_vec.size();
    return 0;
}