// 思路： 埃氏筛，时间Onloglogn，空间On
// 1. 找到一个质数的时候，将其倍数的数都记为非质数
// 2. 倍数可以不是从头开始，因为对于一个质数x，他的2x，3x……,如果系数小于x，那么其实已经被计算过
// 3. 因此系数可以从x开始

class Solution {
public:
    int countPrimes(int n) {
        vector<bool> is_prime(n, true);
        int res = 0;
        for (int i = 2; i < n; ++ i) {  //从2开始记录
            if (is_prime[i]) {          //如果这个数是质数，质数+1
                ++ res;
                if (i <= n / i) {       //如果这个数小于根号n，还可以记录一下倍数为非质数，否则已经被记录过，无意义
                    for (int j = i; j <= n / i; ++ j) { //这里判断要加等号因为一来避免超过整数范围，所以采用了除法；二来防止去整导致漏判
                        if (j * i >= n) {   //如果已经达到n，则可以结束本轮for
                            break;
                        }
                        is_prime[j * i] = false;    //否则的话将倍数置为非质数
                    }
                }
            }
        }
        return res;
    }
};