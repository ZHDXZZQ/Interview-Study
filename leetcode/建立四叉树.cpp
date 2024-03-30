/*
// Definition for a QuadTree node.
class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;
    
    Node() {
        val = false;
        isLeaf = false;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }
    
    Node(bool _val, bool _isLeaf) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }
    
    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};
*/

// 思路： 递归，可以采用二维前缀和优化，时间On^2，空间On^2递归栈空间
// 1. 按照题意构造模拟即可，具体看注释
// 2. 有关二维前缀和优化，就是避免多次计算子矩阵的和，这里并没有使用，有兴趣的同学可以学习一下

class Solution {
public:
    Node* sub_con(vector<vector<int>>& g, int x, int y, int len) {  //x和y表示当前子矩阵的左上角开头节点，len表示矩阵边长
        int sum = 0;        //计算当前子矩阵的和
        for (int i = 0; i < len; ++ i) {
            for (int j = 0; j < len; ++ j) {
                sum += g[x + i][y + j];
            }
        }
        if (sum == 0 || sum == len * len) { //如果子矩阵满足全1或者全0，直接构造该子矩阵作为叶子节点
            return new Node(sum / (len * len), true);
        }
        auto topleft = sub_con(g, x, y, len / 2);       //否则的话递归建立子矩阵
        auto topright = sub_con(g, x, y + len / 2, len / 2);
        auto bottomleft = sub_con(g, x + len / 2, y, len / 2);
        auto bottomright = sub_con(g, x + len / 2, y + len / 2, len / 2);
        return new Node(-1, false, topleft, topright, bottomleft, bottomright);
    }

    Node* construct(vector<vector<int>>& grid) {
        int n = grid.size();    //对大矩阵进行计算
        int sum = 0;
        for (int i = 0; i < n; ++ i) {  //求和
            for (int j = 0; j < n; ++ j) {
                sum += grid[i][j];
            }
        }
        if (sum == n * n || sum == 0) { //如果全部为0或者全部为1，则直接建立该节点为叶子节点，返回即可
            return new Node(sum / (n * n), true);
        }
        auto topleft = sub_con(grid, 0, 0, n / 2);  //这里不能提前定义Node*，不然会提示没有重载运算符=
        auto topright = sub_con(grid, 0, n / 2, n / 2); //如果不为0，则构造他的四叉树
        auto bottomleft = sub_con(grid, n / 2, 0, n / 2);
        auto bottomright = sub_con(grid, n / 2, n / 2, n / 2);
        return new Node(-1, false, topleft, topright, bottomleft, bottomright); //返回构造的四叉树
    }
};