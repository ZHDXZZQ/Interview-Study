//找出某个数的所有的质因数
// 思路： 试除法，时间O根号n，空间O1
//同类型的，判断质数、寻找约数

#include <iostream>
#include <algorihtm>
using namespace std;
unordered_map<int, int> rec;    //rec中存储每个质因数的个数，直接cout输出也可以
void divide(int n) {
    for (int i = 2; i <= n / i; ++ i) { //只用到根号n就行了，超过的就是重复的
        if (n % i == 0) {    //这个i一定是质数，且是它的因子，因为如果有比i还小的数能整除i，那么前面一定已经除完了
            while (n % i == 0) {    //将i这个质因数除干净
                n /= i;
                rec[i] ++;
            }
        }
    }
    if (n > 1) {
        rec[n] ++;      //如果最后的值不是1，说明这个值也是一个质因数
    }
}