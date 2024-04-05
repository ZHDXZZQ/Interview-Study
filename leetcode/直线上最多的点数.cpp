//思路： 哈希表，计算斜率并记录， 时间n^2，空间n^2，其中n为点的个数
// 1. 对于任意两个点，计算斜率和截距，将其存储起来
// 2. 对于斜率为无穷的，也就是垂直于x轴的，单独存起来

class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        unordered_map<double, unordered_map<double, unordered_set<string>>> line; //k -> b -> point
        //外层map的key表示斜率，内层map的key表示截距，内层set存储当前k和b上的点
        int res = 1;        //初始为1，如果只有一个点，自然他在一条直线上
        unordered_map<int, unordered_set<string>> k_inf;    //存储垂直于x轴的直线上的点，key为距离原点的距离，value为点
        int n = points.size();
        for (int i = 0; i < n; ++ i) {  //遍历每个点
            auto& point_1 = points[i];
            int& x1 = point_1[0];
            int& y1 = point_1[1];
            for (int j = i + 1; j < n; ++ j) {  //再遍历其他的点，已经计算过的两点不再重复计算
                auto& point_2 = points[j];
                int& x2 = point_2[0];
                int& y2 = point_2[1];
                double x = x2 - x1;
                double y = y2 - y1;
                if (x == 0) {       //x等于0时，y一定不等于0
                    string p1 = to_string(x1) + to_string(y1);  //此时，这两点所在的直线垂直于x轴
                    string p2 = to_string(x2) + to_string(y2);
                    k_inf[x1].insert(p1);
                    k_inf[x1].insert(p2);   //unordered_set会自动去重
                    res = max(res, int(k_inf[x1].size()));
                    continue;
                }
                double k = y / x;       //计算斜率和截距
                double b = y2 - k * x2;
                string p1 = to_string(x1) + to_string(y1);  //将点转化为字符串存储
                string p2 = to_string(x2) + to_string(y2);
                line[k][b].insert(p1);      //记录该直线上的该点
                line[k][b].insert(p2);
                res = max(res, int(line[k][b].size())); //更新答案
            }
        }
        return res;
    }
};