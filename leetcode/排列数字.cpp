/*
    思路： dfs回溯，时间On!，空间On递归栈空间
    1. 用一个vec存当前结果
    2. 用一个set记录当前没有用哪些数字来提速
    3. 每次插入未插入的数字，如果个数不够，就接着dfs插入
    4. 如果个数满足，则打印当前数字
    5. 每次dfs完之后要回溯
*/

#include <iostream>
#include <set>  // 之所以用set是因为uset会乱序输出，无法通过，其实可以用uset
#include <vector>

using namespace std;

vector<int> cur_res;
set<int> unused_num;

void dfs(int& n) {
    if (cur_res.size() == n) {  // 如果当前结果的个数满足，则打印当前结果
        for (auto& x : cur_res) {
            cout << x << " ";
        }
        cout << endl;
        return;
    }
    vector<int> candidates(unused_num.begin(), unused_num.end());   
    // 用vec来记录一下当前未插入的数字，否则直接用uset边遍历边修改会出错
    for (auto& num : candidates) { // 遍历所有未插入的数
        cur_res.push_back(num); // 插入进行dfs
        unused_num.erase(num);
        dfs(n);
        unused_num.insert(num); // 回溯
        cur_res.pop_back();
    }
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++ i) { // 从1到n依次插入
        unused_num.insert(i);
    }
    dfs(n);
    return 0;
}