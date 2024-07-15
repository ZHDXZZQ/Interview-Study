/*
    约数：可以除尽的数
    思路： 试除法，时间On√n，空间On
*/

#include <iostream> 
#include <algorithm>
#include <vector>

using namespace std;

void get_div(int& x) {
    vector<int> res;
    for (int i = 1; i <= x / i; ++ i) { // 还是除到一半即可
        if (x % i == 0) {   // 如果这个数能除尽
            res.emplace_back(i);    // 这个数是一个约束
            if (i != x / i) {   // 如果另一个约数不为i，则也插入
                res.emplace_back(x / i);
            }
        }
    }
    sort(res.begin(), res.end());   // 排序输出
    for (auto& num : res) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    int n;
    cin >> n;
    while (n --) {
        int x;
        cin >> x;
        get_div(x);
    }
    return 0;
}