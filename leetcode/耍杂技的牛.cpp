/*
    思路： 贪心，时间Onlogn，空间On
    对总和排序，按从小到达往下叠罗汉，风险的最大值最小
    1. 起始只要证明贪心解>=最优解，贪心解<=最优解即可，前者显而易见。
    2. 对于后者，我们只要做一组反证法即可，比如a1 + a2 < b1 + b2
    3. 对于这两头牛的顺序变化，是不会影响上下其他牛的，因此可以颠倒计算一下
    4. 假设上面的牛的重量为x
    5. 如果a在b的上面，a的风险为x-a2，b的风险为x+a1-b2
    6. 如果b在a的上面，a的风险为x+b1-a2，b的风险为x-b2
    7. 对上面四个式子分别+a2+b2-x，不影响相对大小，变成了
    8. b2和a1+a2
    9. b1+b2和a2
    10. 因为a1 + a2 < b1 + b2且都为正数，因此b在a的上面的一种情况b1+b2一定大于b2和a1+a2
    11. 因此无论a2是什么，b在a的上面的最大风险一定大于a在b的上面的最大风险，即不是最优解
    12. 因此按总和排序后的最大风险的最小值最小
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> nums(n, vector<int>(3));    // 分别存储总和，重量，强壮度
    for (int i = 0; i < n; ++ i) {
        cin >> nums[i][1] >> nums[i][2];
        nums[i][0] = nums[i][1] + nums[i][2];
    }
    sort(nums.begin(), nums.end()); // 按总和排序
    int res = -1e9;
    int weight = 0; // 记录上面的重量之和
    for (int i = 0; i < n; ++ i) {
        int fengxian = weight - nums[i][2]; // 计算风险
        res = max(res, fengxian);   // 记录风险的最大值
        weight += nums[i][1];   // 重量加上
    }
    cout << res << endl;
    return 0;
}