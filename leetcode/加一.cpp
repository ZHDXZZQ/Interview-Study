// 思路： 判断末尾有多少9，时间On，空间O1
// 1. 从后往前遍历，碰到9则变成0，继续往前遍历，直到碰到第一个非9的数，自增一并停止遍历，返回即可
// 2. 如果全部都是9，则要把第一个数变成1，并在末尾多加入一个0即可

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int n = digits.size();
        for(int i = n - 1; i >= 0 ; -- i) { //从后往前遍历
            if(digits[i] == 9) {            //如果当前数为9
                digits[i] = 0;              //将其变0并继续遍历
                if(i == 0) {                //如果已经遍历到最左边且还是9，则说明全是9
                    digits[i] = 1;          //此时需要把当前值改为1，并在末尾插入一个0即可
                    digits.push_back(0);
                }
            } else {                        //当碰到非9的数时，将当前位置自增然后返回即可
                ++ digits[i];
                break;
            }
        }
        return digits;
    }
};