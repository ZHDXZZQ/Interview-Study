/*
    思路： 贪心，时间Onlogn，空间On
    1. 先将区间按左端点排序，我们贪心尽量要找左端点升序的，保证后面没有左端点更靠里的
    2. 维护一个小根堆存储所有现有的区间的右端点
    3. 每次判断当前区间与堆顶区间右端点的关系，此时堆顶的区间右端点为最靠左的区间，如果此时仍然不能合并，说明这个区间的左端点更靠左，而又比之前区间的右端点都靠左，所以只能重新开一个区间
    4. 如果当前区间的左端点与堆顶最左区间的右端点不重叠，则更新堆顶区间的右端点为当前区间的右端点，属于合并入
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> nums(n, vector<int>(2, 0));
    for (int i = 0; i < n; ++ i) {
        cin >> nums[i][0] >> nums[i][1];
    }
    sort(nums.begin(), nums.end()); // 左端点升序
    priority_queue<int, vector<int>, greater<int>> sections;    // 优先队列小根堆
    for (int i = 0; i < n; ++ i) {
        if (sections.size() && sections.top() < nums[i][0]) {   // 如果当前区间的左端点能插入到堆顶区间，即比堆顶区间的右端点靠右
            sections.pop(); // 则把堆顶区间的右端点弹出，插入新的右端点
        }
        sections.push(nums[i][1]);  // 否则如果连堆顶区间都不能插入，则后面的更不能插入，则直接插入该区间作为一个新开的区间
    }
    cout << sections.size();
    return 0;
}