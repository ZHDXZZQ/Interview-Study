// 具体解释请看本站八股/算法模板中的merge_sort

#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int a[N];

void merge_sort(int q[], int l, int r)
{
    if (l >= r) return;
    int mid = l + r >> 1;
    merge_sort(q, l, mid), merge_sort(q, mid + 1, r);  //在开始前先递归，到每个归并段为1个元素
    int tmp[N];  //相当于缓存
    int k = 0, i = l, j = mid + 1;
    while (i <= mid && j <= r)  //两段都没结束
        if (q[i] <= q[j]) tmp[k ++ ] = q[i ++ ];  //小的那个写到缓存
        else tmp[k ++ ] = q[j ++ ];
    while (i <= mid) tmp[k ++ ] = q[i ++ ];  //前面已经有一个到头了，另一个没到头的接到后面去
    while (j <= r) tmp[k ++ ] = q[j ++ ];
    for (i = l, j = 0; i <= r; i ++, j ++ ) q[i] = tmp[j];  //把这两段排序后重写
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i ++ ) scanf("%d", &a[i]);
    merge_sort(a, 0, n - 1);
    for (int i = 0; i < n; i ++ ) printf("%d ", a[i]);
    return 0;
}
