/*
    思路： 二分，时间Ologn，空间O1
*/

#include <iostream>

using namespace std;

int main()
{
    double x;
    cin >> x;

    double l = -100, r = 100;   // 左右边界，n的开3次方最大也到不了-100到100
    while (r - l > 1e-8) {  // 因为是浮点数，且结果保留六位小数，因此设置一个l和r的阈值
        double mid = (l + r) / 2;   // 找到中间数
        if (mid * mid * mid >= x) { r = mid; }  // 如果中间数的三次方比目标值大，则在mid的右边（包含右边界）
        else { l = mid; }   // 否则目标值在左边
    }

    printf("%.6lf\n", l);   // 输出结果
    return 0;
}