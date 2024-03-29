// 思路： 展开二分，时间Ologmn，空间O1
// 1. 所有数字从左往右递增，上一行末大于本行头，将其按顺序展开是一个长度为mn的递增序列
// 2. 对其进行二分即可，只需考虑将当前的下标转换成二维的即可

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();
        int sum = m * n;
        int l = 0;
        int r = sum - 1;    //二分的两个边界，将所有行拼接看作一个数组
        while (l < r) {     //标准二分模版
            int mid = (l + r) / 2;
            int x = mid / n;    //只需处理一下位置所代表的坐标即可
            int y = mid % n;
            int cur_val = matrix[x][y];
            if (cur_val >= target) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        int x = r / n;  //最后判断一下找到的位置是否为目标数字，如果是则存在，否则不存在
        int y = r % n;
        if (matrix[x][y] == target) { return true; }
        return false;
    }
};