/*
    思路： 排序后拼接，时间Onlogn排序耗时，空间O1.
    上方有类似的题目，叫 合并区间，本题直接看注释或者查阅原题
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> lr_vec(n, vector<int>(2));  // 存储所有区间
    for (int i = 0; i < n; ++ i) {
        cin >> lr_vec[i][0] >> lr_vec[i][1];
    }
    sort(lr_vec.begin(), lr_vec.end()); // 按区间左端点排序
    int l = lr_vec[0][0], r = lr_vec[0][1]; // 初始化当前区间，即是否有合并
    int res = 1;    // 初始化结果为1，因为最后一个区间没有合并计入
    for (int i = 1; i < n; ++ i) {  // 从第二个区间开始遍历
        int& cur_l = lr_vec[i][0];  // 获取当前遍历区间的所有端点
        int& cur_r = lr_vec[i][1];
        if (cur_l <= r) {   // 如果当前区间的左端点小于当前合并后区间的右端点，说明该区间也可以合并入
            r = max(r, cur_r);  // 更新当前合并区间的右端点
        } else {    // 否则的话，该区间属于下一个区间的起始区间
            ++ res; // 当前区间合并完成
            l = cur_l;  // 更新待合并区间的左右端点
            r = cur_r;
        }
    }
    cout << res << endl;
    return 0;
}