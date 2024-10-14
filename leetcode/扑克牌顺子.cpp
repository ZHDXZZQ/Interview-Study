/*
    思路： 排序，时间Onlogn，空间O1
*/

class Solution {
public:
    bool IsContinuous(vector<int>& numbers) {
        // write code here
        sort(numbers.begin(), numbers.end());   // 排序
        int zero_cnt = 0;   // 记录0的个数
        int pos = 0;    // 记录第一个非0数的位置
        while (pos < 5) {
            if (numbers[pos] == 0) {
                ++ zero_cnt;
                ++ pos;
            } else {
                break;
            }
        }

        // 判断是否有非0的数字重复，如果重复，则不可能是顺子
        for (int i = pos; i < 5; ++ i) {
            if (numbers[i] == numbers[i - 1]) {
                return false;
            }
        }

        // 记录非0的个数
        int cnt = 5 - pos;
        int gap = numbers.back() - numbers[pos];    // 记录非0数最小和最大值的差距
        if (zero_cnt + cnt > gap) { // 如果0的个数加上非0的个数比差距大，说明能组成顺子
            return true;
        }
        return false;   // 否则不能
    }
};