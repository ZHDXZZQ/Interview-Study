/*
    思路： 二分， 时间Omlogm+nlogm，空间Ologm
*/

class Solution {
public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        sort(potions.begin(), potions.end());   // potions按序排列
        int n = spells.size();
        int m = potions.size();
        vector<int> res(n, 0);
        for (int i = 0; i < n; ++ i) {
            long long first = spells[i];    // 每次拿左边的一个数
            int l = 0, r = m - 1;
            int mid = 0;
            while (l < r) { // 在右边二分
                mid = (l + r) / 2;
                if ((long long)(potions[mid]) * first >= success) {
                    r = mid;
                } else {
                    l = mid + 1;
                }
            }
            if (l == m - 1 && (long long)(potions[m - 1]) * first < success) {  // 如果都不能超过success，则为0
                res[i] = 0;
            } else {
                res[i] = m - r; // 否则为差
            }
        }
        return res;
    }
};