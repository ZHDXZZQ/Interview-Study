// 思路： 简单动规，时间On，空间O1
// 1. 假设跳到n层，这个n >= 2，那么他只能从n - 1层跳来，或从n - 2层跳来
// 2. 所以他跳到n层的方法，就是跳到n - 1层的方法加上n - 2层的方法
// 3. 举个例子，0层到2层是一种方法；0层到1层再到2层是一种方法，那么到2层，就是到达0层的方法加上到达1层的方法
// 4. 因为到达1层固定只有1种方法，0层本身不需要动，直接开始跳到2层也是1种方法，故有2种方法

class Solution {
public:
    int climbStairs(int n) {
        if(n == 1) return 1;
        int twoStair = 1, oneStair = 1;     //two代表到达n-2层的方法数，one代表到达n-1层的方法数
        int res = 0;
        for(int i = 1; i < n; ++ i) {
            res = twoStair + oneStair;      //到达该层的方法数，是二者之和
            twoStair = oneStair;            //对于下一层来说，更新二者的值
            oneStair = res;
        }
        return res;
    }
};