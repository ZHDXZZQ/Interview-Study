/*
    思路： 模拟，时间On，空间O1
    1. 只需遍历一遍，把所有能插花的位置插上花，判断是否满足n个即可
    2. 无需考虑是否此处能插但不插更好，因为只需要考虑插花最多的情况
*/

class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        int size = flowerbed.size();
        if (size == 1) {    // 如果只有一个花坛
            if (n == 0 || (flowerbed[0] == 0 && n == 1)) { return true; }
            else return false; // 如果不需要插花或者当前位置可以插花则为true
        }
        for (int i = 0; i < size; ++i) {    // 从前往后遍历花坛
            if (i == 0) {   // 对头尾特殊处理
                if (flowerbed[0] == 0 && flowerbed[1] == 0) {   // 如果头部能插花
                    flowerbed[0] = 1;   // 插花
                    --n;    // 成功插一个
                }            
            } else if (i == size - 1) { // 如果尾部能插花
                if (flowerbed[size - 1] == 0 && flowerbed[size - 2] == 0) {
                    flowerbed[size - 1] = 1;    // 插花成功一个
                    --n;
                }
            } else {    // 中间只需判断当前位置和两个旁边是否有空位
                if (flowerbed[i] == 0 && flowerbed[i - 1] == 0 && flowerbed[i + 1] == 0) {
                    flowerbed[i] = 1;   // 如果有，则插花成功
                    --n;
                }
            }
        }
        return n <= 0;
    }
};