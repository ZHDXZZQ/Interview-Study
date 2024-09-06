/*
    思路： 贪心，时间Onlogn，空间On
    1. 将所有区间按照左端点先排列
    2. 每次找到左端点不超过当前开始区间左端点的区间，记录最大右端点
    3. 当某次区间左端点超过了当前开始区间的左端点时，更新当前开始区间的左端点为之前记录的最大右端点
    4. 重复上述步骤，判断是否能够覆盖所有区间
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int start, end;
    cin >> start >> end;
    int n;
    cin >> n;
    vector<vector<int>> nums(n, vector<int>(2));
    for (int i = 0; i < n; ++ i) {
        cin >> nums[i][0] >> nums[i][1];
    }
    sort(nums.begin(), nums.end()); // 排序

    int res = 0;
    int pos = 0;
    int cur_right = start;  // 记录当前最大右端点
    bool flag = false;
    while (pos < n) {
        if (nums[pos][0] > start && start != cur_right) {   // 如果当前区间的左端点已经超过了起始左端点，并且最大右端点不和起始左端点重合
            start = cur_right;  // 更新开始区间的左端点，表明前面已经有一个区间覆盖了原始start到cur_right
            ++ res; // 区间+1
        }
        if (nums[pos][0] <= start && nums[pos][1] >= cur_right) {   // 如果当前区间的左端点小于等于目标区间的左端点且最大右端点更大
            cur_right = nums[pos][1];   // 记录最大右端点
            flag = true;    // 标记为更新过一次
        }
        if (cur_right >= end && flag) { // 如果某次最大右端点已经大于终点，并且至少更新过一次（避免起始区间右端点大于目标右端点）
            ++ res; // 找到答案，插入该区间，结束循环
            break;
        }
        ++ pos; // 判断下一个区间
    }
    if (cur_right < end || res == 0) {  // 如果当前右区间没有达到终点或者结果中没有区间
        cout << -1 << endl; // 返回-1
    } else {
        cout << res << endl;
    }
    return 0;
}

// y总写法，效率快10倍，什么原因
// #include <iostream>
// #include <algorithm>

// using namespace std;

// const int N = 100010;

// int n;
// struct Range
// {
//     int l, r;
//     bool operator< (const Range &W)const
//     {
//         return l < W.l;
//     }
// }range[N];

// int main()
// {
//     int st, ed;
//     scanf("%d%d", &st, &ed);
//     scanf("%d", &n);
//     for (int i = 0; i < n; i ++ )
//     {
//         int l, r;
//         scanf("%d%d", &l, &r);
//         range[i] = {l, r};
//     }

//     sort(range, range + n);

//     int res = 0;
//     bool success = false;
//     for (int i = 0; i < n; i ++ )
//     {
//         int j = i, r = -2e9;
//         while (j < n && range[j].l <= st)
//         {
//             r = max(r, range[j].r);
//             j ++ ;
//         }

//         if (r < st)
//         {
//             res = -1;
//             break;
//         }

//         res ++ ;
//         if (r >= ed)
//         {
//             success = true;
//             break;
//         }

//         st = r;
//         i = j - 1;
//     }

//     if (!success) res = -1;
//     printf("%d\n", res);

//     return 0;
// }
