// 思路： 排序后巧妙遍历，时间Onlogn，空间O1
// 1. 按引用次数从小到大排序
// 2. 遍历时，后面的文献的引用次数一定大于当前文献的引用次数
// 3. 因此可以同时选出引用次数更多且文献数量更多的n

class Solution {
public:
    int hIndex(vector<int>& citations) {
        int c_size = citations.size();
        sort(citations.begin(), citations.end());  //按被引用次数从小到大排序
        int res = 0;
        for(int i = 0; i < c_size; ++ i) {  //从引用次数小的文献往后遍历，c_size - i表示后面有这么多个文献的引用次数大于citations[i]次
            res = max(res, min(c_size - i, citations[i]));
            //首先，res按更大来更新；其次，后面两者的最小值即为题目中的n，表明至少有n个文献被引用了n次
        }
        return res;
    }
};