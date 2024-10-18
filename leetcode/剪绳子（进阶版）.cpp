class Solution {
  public:
    long long mod = 998244353;
    //快速乘法
    long long fast(long long x, long long y) {
        long long res = 0;
        x %= mod;
        y %= mod;
        while (y) {
            if (y & 1) {
                //加法代替乘法，防止越界
                res += x;
                if (res >= mod)
                    res -= mod;
            }
            y = y >> 1;
            x = x << 1;
            if (x >= mod)
                x -= mod;
        }
        return res;
    }
    //快速幂
    long long Pow(long long x, long long y) {
        long long res = 1;
        while (y) {
            //可以再往上乘一个
            if (y & 1)
                res = fast(res, x);
            //叠加
            x = fast(x, x);
            //减少乘次数
            y = y >> 1;
        }
        return res;
    }
    long long cutRope(long long number) {
        //不超过3直接计算
        if (number <= 3)
            return number - 1;
        //能整除3
        if (number % 3 == 0)
            return Pow(3, number / 3);
        //最后剩余1
        else if (number % 3 == 1)
            //4*3^{n-1}
            return fast(Pow(3, number / 3 - 1), 4);
        //最后剩余2
        else
            //2*3^n
            return fast(Pow(3, number / 3), 2);
    }
};
