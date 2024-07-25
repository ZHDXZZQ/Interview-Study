// 具体解释请看本站八股/算法模板中的quick_sort

#include<bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

int n;
int q[N];

void quick_sort(int q[], int l, int r) {  //取中点作为要确定的点
    if(l >= r) return;
    int x = q[l + r >> 1], i = l - 1, j = r + 1;
    while(i < j) {
        do i ++; while(q[i] < x);  //i找到一个大于或等于x的
        do j --; while(q[j] > x);  //j找到一个小于或等于x的
        if(i < j) swap(q[i], q[j]);  //当前找完，符合情况就交换
    }
    quick_sort(q, l, j);
    quick_sort(q, j + 1, r);
}

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i ++) scanf("%d", &q[i]);
    quick_sort(q, 0, n - 1);
    for(int i = 0; i < n; i ++) printf("%d ", q[i]);
    return 0;
}