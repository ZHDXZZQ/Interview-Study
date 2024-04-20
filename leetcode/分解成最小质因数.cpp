//找出某个数的所有的质因数，时间O根号n，空间O1
//同类型的，判断质数、寻找约数
#include <iostream>
#include <algorihtm>
using namespace std;
unordered_map<int, int> rec;    //rec中存储每个质因数的个数，直接cout也可以
void divide(int n) {
    for (int i = 2; i <= n / i; ++ i) { //只用到根号n就行了，超过的就是重复的
        if (n % i == 0) {    //这个i一定是质数，且是它的因子
            while (n % i == 0) {
                n /= i;
                rec[i] ++;
            }
        }
    }
    if (n > 1) {
        rec[n] ++;      //如果最后的值不是1，说明这个值也是一个质因数
    }
}