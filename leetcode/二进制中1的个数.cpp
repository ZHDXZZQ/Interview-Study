/*
    思路： lowbit实现，时间Os，空间O1，s为结果
*/

#include <iostream>

using namespace std;

int main()
{
    int n;
    scanf("%d", &n);
    while (n --)
    {
        int x, s = 0;
        scanf("%d", &x);

        for (int i = x; i; i -= i & -i) {   // i & -i就是只保留当前i的最后一个1，而其他都为0构成的数，减去的次数就是1的个数
            s ++ ;
        }

        printf("%d ", s);
    }

    return 0;
}