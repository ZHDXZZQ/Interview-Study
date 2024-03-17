// 思路：二分法，时间Ologx，空间O1
// 1. 每次二分判断当前值的平方和x的关系，然后细分区间

class Solution {
public:
    int mySqrt(int x) {
        int l = 0, r = x;
        while (l < r) {
            int mid = (l + r + 1ll) / 2;    //1ll表示longlong类型的1，防止l+r+1溢出int，因为下面的判断是l=mid，所以要加1，不然可能会死循环，例如x=8的情况
            if (mid <= x / mid) {   //这里原本是mid * mid <= x，但是mid的平方可能会溢出int，所以以该方式书写
                l = mid;            //如果mid的平方小于等于，那么目标值一定在mid及其右边
            } else {
                r = mid - 1;        //否则一定在mid左边
            }
        }
        return r;                   //此处返回r或l皆可以
    }
};


//另外力扣官方使用数学的ln和e来求，时间O1，空间O1，叫做袖珍计算器算法，感兴趣的同学可以ctrl+左键看看->https://leetcode.cn/problems/sqrtx/solutions/238553/x-de-ping-fang-gen-by-leetcode-solution/?envType=study-plan-v2&envId=top-interview-150