// 思路： Floyd算法，图论，时间On^3，空间On^2
// 1. 与佛洛依德算法不同的是，本题任两点间的距离是固定的，不存在寻找最小值的情况。

class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        unordered_set<string> nodes;  //顶点集
        unordered_map<string, unordered_map<string, double>> vals;  //边集，也就是商
        vector<double> res;

        //构造顶点集和边集
        int n = values.size();
        for (int i = 0; i < n; i ++) {
            string& k = equations[i][0];
            string& v = equations[i][1];
            double cur_res = values[i];
            nodes.insert(k), nodes.insert(v);
            vals[k][v] = cur_res, vals[v][k] = 1 / cur_res;
        }

        //计算任意两点之间的路径，也就是商，找到所有可能得到的公式。注意，最外层循环的结点是中转结点。
        for (auto& y : nodes) {
            for (auto& x : nodes) {
                for (auto& z : nodes) {
                    if (vals.find(x) != vals.end() && vals[x].find(y) != vals[x].end() && vals.find(y) != vals.end() && vals[y].find(z) != vals[y].end()) {
                        vals[x][z] = vals[x][y] * vals[y][z];
                    }
                }
            }
        }

        //查询
        for (auto& vec : queries) {
            string& k = vec[0];
            string& v = vec[1];
            if (vals.find(k) != vals.end() && vals[k].find(v) != vals[k].end()) {
                res.push_back(vals[k][v]);
            }
            else {
                res.push_back(-1.0);
            }
        }
        return res;
    }
};