/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

// 思路： 改进层次遍历，时间On，空间O1
// 1. 在遍历当前层的时候，构造下一层的拉链，但是要记录一下拉链头，方便下一层构造

class Solution {
public:
    Node* connect(Node* root) {
        if (!root) { return root; } //特判，如果为空则返回空
        auto cur = root;            //从根节点开始遍历，根节点的next初始化位null不用管，且第一层无需构建
        while (cur) {               //cur作为判断当前层是否有节点，用于表示每一层的第一个节点
            Node* head = new Node(-1);  //为下一层建立一个头节点
            auto tail = head;       //建立一个尾节点，用于追加链表的节点
            for (auto p = cur; p; p = p->next) {    //p指向该层第一个节点，顺序遍历该层所有节点
                if (p->left) {      //如果p的左孩子存在
                    tail->next = p->left;   //将该节点插入下一层的链表中
                    tail = tail->next;  //更新链表尾
                }
                if (p->right) {     //将p的右孩子加入下一层的链表中
                    tail->next = p->right;
                    tail = tail->next;
                }
            }
            cur = head->next;   //该层遍历完后，执行下一层，cur指向下一层的第一个节点，同时判断是否还有下一层
        }
        return root;    //返回根节点即可
    }
};