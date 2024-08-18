/*
    基数排序： 基于关键字各位的大小进行排序
    一种是最高位优先MSD：按关键字位权重递减依次逐层划分成若干更小的子序列，然后合成一个有序序列
    最低为优先LSD：按关键字位权重递增依次逐层划分成若干更小的子序列，然后合成一个有序序列
    举例对于正整数排序，基数r=10
    时间复杂度为Odn，d为最大数字的位数
    空间复杂度On
    稳定的算法
*/

#include <algorithm>
#include <vector>
#include <math.h>
#include <queue>

using namespace std;

template <class T>
void BaseSort(std::vector<T>& nums) {
    int n = nums.size();
    vector<queue<int>> single_bit_list(10); 
    int r = 10;
    int bit_cnt = 0;
    for (auto num : nums) { // 计算最大数字的位数，按每位的大小来多轮排序
        int cur_bit = 0;
        while (num) {
            num /= r;
            ++ cur_bit;
        }
        bit_cnt = max(bit_cnt, cur_bit);
    }

    for (int i = 0; i < bit_cnt; i ++) {    // 遍历每一位

        for (auto& num : nums) {
            int v = (num / static_cast<int>(pow(r, i))) % r;    // 取出当前位的值
            single_bit_list[v].push(num);   // 将该数字根据当前位的值的位置，插入到对应队列中
        }

        int ptr = 0;
        for (auto& q : single_bit_list) {   // 取出每个队列中的数字，即对当前位进行了排序
            while (q.size()) {
                nums[ptr] = q.front();
                q.pop();
                ++ ptr;
            }
        }

    }
    return;
}