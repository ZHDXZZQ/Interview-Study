/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

// 思路： 图的遍历， 时间On，空间On
// 1. 要遍历原图中所有节点，所以要把原图中的节点（指针）都存起来方便遍历，这里采用边遍历边动态存储
// 2. 对于每个节点，根据其值新建节点。
// 3. 对于每个节点的邻居，根据邻居值找到新建的节点，或新建邻居节点，然后将该邻居节点存入新建节点的邻居中

class Solution {
public:
    Node* cloneGraph(Node* node) {
        if(node == nullptr) return nullptr;     //如果原图为空，直接返回空
        unordered_map<int, Node*> i2n;          //建立新建图中节点值对节点的映射
        vector<Node*> used;                     //存储原有的图的所有节点，保证全部遍历一遍
        used.push_back(node);                   //先插入初始节点1，即输入节点，方便开启遍历
        auto root = new Node(1);                //创建返回结果的1号节点
        i2n[1] = root;                          //将其映射为1
        for(int i = 0; i < used.size(); ++ i) { //该方式可保证动态扩充后继续遍历新扩充的节点
            auto& it = used[i];                 
            auto& cur_node = i2n[it->val];      //但凡是used中的节点，一定已经新建节点，所以找到该新建的节点插入邻居即可
            for(auto& neighbor : it->neighbors) {//遍历原图中该节点的每个邻居
                if(i2n.find(neighbor->val) == i2n.end()) {  //如果原图中的这个邻居还没有新建，说明是第一次遍历到这个值的邻居节点
                    used.push_back(neighbor);       //将该邻居插入used中，方便后续遍历
                    auto n = new Node(neighbor->val);   //根据该值新建节点
                    i2n[neighbor->val] = n;         //将新建节点插入映射表中
                    cur_node->neighbors.push_back(n);   //将该新建邻居节点插入到刚遍历到的节点的邻居中
                } else {
                    auto neighbor_node = i2n[neighbor->val];    //如果该邻居节点已经新建，则直接找到
                    cur_node->neighbors.push_back(neighbor_node); //将该邻居节点插入到刚遍历到的节点的邻居中
                }
            }
        }
        return root;        //返回1号节点，也可是i2n[1]
    }
};



// 递归版解法
// class Solution {
// 	   unordered_map<Node*, Node*> oldnew, newold;// 新老节点一一对应
// public:
//     // 建图并返回node对应的新节点newNode
//     Node* cloneGraph(Node* node) {
//         if (!node)return nullptr;
//         if (oldnew.count(node)) {
//             return oldnew[node];// 对应的newNode已经创建过了
//         }
//         // 创建newNode
//         Node* newNode = new Node(node->val);
//         oldnew[node] = newNode, newold[newNode] = node;
//         for (Node* neighbor : node->neighbors) {
//             Node* newNeighbor = cloneGraph(neighbor);
//             newNode->neighbors.push_back(newNeighbor);
//         }
//         return newNode;
//     }
// };