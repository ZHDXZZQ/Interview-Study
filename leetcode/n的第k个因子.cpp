// 思路： 折半筛选，时间O根号n，空间O1
// 1. 首先计算到目标值的根号位置，记录当前因子个数
// 2. 判断目标因子在前在后，具体处理即可

class Solution {
public:
    int kthFactor(int n, int k) {
        int cnt = 0;
        int i;
        for (i = 1; i <= n / i; ++ i) { //记录一直到根号n的情况下的因子个数
            if (n % i == 0) {
                ++ cnt;
            }
        }
        if (k > cnt * 2 || (pow(i - 1, 2) == n && k > 2 * cnt - 1)) {
            return -1;      //如果目标值大于2倍，或者在根号位置恰好整除n的情况下目标值大于个数的2倍-1个，此时属于超出范围，返回-1
        }
        bool behind = false;    //记录目标值在根号位置的前后关系
        if (k > cnt) {      //如果k大
            behind = true;  //则目标值在后面
            k -= cnt;       //k用于记录后面找几个
        } else {
            k = cnt - k + 1;    //否则的话在前面，k用于记录从根号位置往前找几个
        }
        for (-- i; i >= 1; -- i) {
            if (i * i == n && behind) { //如果根号位置恰好能整除n，且目标值在后面，则要少算一个
                continue;
            }
            if (n % i == 0) {   //如果当前值是一个因子
                -- k;           //则找到一个
                if (k == 0) {   //当k找到0时
                    if (behind) {   //如果在后，则求商
                        return n / i;
                    } else {        //如果在前，除数就是目标值
                        return i;
                    }
                }
            }
        }
        return -1;
    }
};