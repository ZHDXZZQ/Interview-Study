// 牛牛对n个城市的旅游情况进行了规划已知每个城有两种属性x和y,其中x表示去第i号城市的花费,y表示在第i号城市游玩后会得到的开心值
// 现在牛牛希望从中挑选出一些城市去游玩,但挑选出的城市必须满足任意两个城市之间花费差值的绝对值小于k
// 他想请你帮他计算出在满足上述条件下能得到的最大开心值是多少
// 输入描述:
// 第一行输入两个正整数n和k.
// 按下来n行,每行输入两个整数x和y分别表示每个城市的两种属性
// 1<n≤1000001<k<1000000000
// 0≤x,y≤1000000000输出描述:
// 输出一个整数表示答案
// 例如：
// 输入
// 5 3
// 1 3
// 2 1
// 5 2
// 3 1
// 4 3
// 输出
// 6
// 说明
// 牛牛可以选挥去3号,4号,5号城市这行游玩,并收获最大的开心值
// 思路： 滑动窗口，时间Onlogn，空间On
// 1. 将花费按顺序排列，利用滑动窗口搜索在消费窗口内的城市的开心值之和，求max

#include <iostream>
#include <map>

using namespace std;

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int res = 0;
    map<int, int> cost_happy;
    for (int i = 0; i < n; ++ i) {
        int cost, happy;
        scanf("%d %d", &cost, &happy);
        cost_happy[cost] = happy;
    }
    auto l = cost_happy.begin(), r = cost_happy.begin();    //利用滑动窗口遍历map
    int window = 0;
    while (r != cost_happy.end()) {
        window += r->second;
        while (r->first - l->first >= k) {      //保证窗口内的消费是符合预期的
            window -= l->second;
            ++ l;
        }
        ++ r;
        res = max(res, window);     //记录当前这种消费的最大值
    }
    cout << res;
    return 0;
}