/*
    思路： 归并排序，边排序边统计，时间Onlogn，空间On
*/

#include <iostream>

using namespace std;

typedef long long LL;

const int N = 1e5 + 10;

int a[N], tmp[N];

LL merge_sort(int q[], int l, int r)
{
    if (l >= r) return 0;   // 达到边界，已是最小归并段

    int mid = l + r >> 1;   // 找到中点

    LL res = merge_sort(q, l, mid) + merge_sort(q, mid + 1, r); // 归并左右，记录左右子段的逆序对数量

    int k = 0, i = l, j = mid + 1;
    while (i <= mid && j <= r)  // 只要有一边没有达到边界
        if (q[i] <= q[j]) tmp[k ++ ] = q[i ++ ];    // 如果左边的小于右边的，正常，直接记录
        else    // 如果此时左边的大，因为两边已经是有序的，那么对于右边的这个元素来说，左边的后面的所有的元素都比他大，都是逆序对
        {
            res += mid - i + 1; // 记录对于该元素的逆序对的数量
            tmp[k ++ ] = q[j ++ ];  // 继续看下一个
        }
    while (i <= mid) tmp[k ++ ] = q[i ++ ]; // 扫尾，把两边剩下的元素都放进来
    while (j <= r) tmp[k ++ ] = q[j ++ ];

    for (i = l, j = 0; i <= r; i ++, j ++ ) q[i] = tmp[j];  // 放入原位

    return res;
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i ++ ) scanf("%d", &a[i]);

    cout << merge_sort(a, 0, n - 1) << endl;

    return 0;
}