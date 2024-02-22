// 思路： 有限状态机， 时间Omn，空间O1
// 1. 用四种状态来表示本次往哪个方向遍历
// 2. 用四个边界用来表示每次遍历的尽头
// switch case语法：匹配执行，没有break则顺序执行，没有匹配项走default（非必需）

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        char status = 'r';  //状态，r表示往右走，u表示往上走，d表示往下走，l表示往左走
        vector<int> res;
        int m = matrix.size();
        int n = matrix[0].size();
        int up = 0, lt = 0, rt = n, dn = m; //四个边界，up表示上边界，lt表示左边界，rt表示右边界，dn表示下边界
        while(up < dn && lt < rt) {     //只要边界没有重合则有块没有遍历到，只要有任意一组边界重合，则全部遍历完毕
            switch(status) {
                case 'r': {
                    for(int i = up, j = lt; j < rt; ++ j) {     //从左往右遍历
                        res.push_back(matrix[i][j]);
                    }
                    status = 'd';       //下次往下遍历
                    ++ up;              //本边界已遍历完，自增
                    break;              //必须有，否则顺序执行了
                }
                case 'd': {
                    for(int i = up, j = rt - 1; i < dn; ++ i) { //从上往下遍历，此时的up已经自增，因此直接用
                        res.push_back(matrix[i][j]);            //rt和dn是边界+1，所以用的时候要-1
                    }
                    status = 'l';
                    -- rt;
                    break;
                }
                case 'l': {
                    for(int i = dn - 1, j = rt - 1; j >= lt; -- j) {    //从右往左遍历
                        res.push_back(matrix[i][j]);
                    }
                    status = 'u';
                    -- dn;
                    break;
                }
                case 'u': {
                    for(int i = dn - 1, j = lt; i >= up; -- i) {    //从下往上遍历
                        res.push_back(matrix[i][j]);
                    }
                    status = 'r';
                    ++ lt;
                    break;
                }
                default: break;
            }
        }
        return res;
    }
};