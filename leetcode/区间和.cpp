/*
    思路： 离散化，时间O(n+m)+(n+2m)log(n+2m)+N，即O(n+m)log(n+m)，空间On+m
    1. 将离散的数字，映射到一个数组的下标，利用这个数组的下标计算前缀
    2. 每一个的前缀和代表一两个离散数字间的和，因为这一段中间是没有数字的
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using PII = pair<int, int>;

const int N = 300010;

vector<int> alls;   // 记录全部可能用到的离散数字
vector<PII> adds, querys;   // 记录离散数字组合
vector<int> discretization(N, 0);   // 离散化映射后的各位置数字的值
vector<int> prefix_sum(N, 0);   // 前缀和

int find(int x) {   // 找到离散数字x在离散化后的映射的位置
    int l = 0, r = alls.size() - 1; // alls代表所有可能出现的数字，将x映射为alls的某个下标
    while (l < r) {
        int mid = l + r >> 1;
        if (alls[mid] < x) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    return r + 1;   // 返回下标+1，这样保留了0，方便做前缀和
}

int main() {
    int n, m;
    cin >> n >> m;
    
    while (n --) {
        int x, c;
        cin >> x >> c;
        adds.push_back({x, c}); // 记录所有加法操作
        alls.push_back(x);  // 将被加的数字记录
    }
    
    while (m --) {
        int l , r;
        cin >> l >> r;
        querys.push_back({l, r});   // 记录所有查询操作
        alls.push_back(l);  // 将被查询的数字记录
        alls.push_back(r);
    }
    
    // 去重
    sort(alls.begin(), alls.end()); // 排序
    alls.erase(unique(alls.begin(), alls.end()), alls.end());   // 去重，unique函数的作用是将所有相邻相同的元素只选择1个并移动到头部，返回没有去重后的所有元素的尾部
    // 删除尾部到原来尾部的元素，剩下的就是去重后的元素
    
    // 处理插入
    for (auto& item : adds) {
        int x = find(item.first);   // 找到每个要加的数组的离散化后的下标
        discretization[x] += item.second;   // 该位置的值加
    }
    
    // 预处理前缀和
    for (int i = 1; i <= alls.size(); i ++ ) {
        prefix_sum[i] = prefix_sum[i - 1] + discretization[i];  // 将离散化映射后的数字做前缀和
    }
    
    // 处理询问
    for (auto& item : querys) {
        int l = find(item.first), r = find(item.second);    // 找到要查询的区间
        cout << prefix_sum[r] - prefix_sum[l - 1] << endl;  // 前缀和求区间和
    }
    
    return 0;
}