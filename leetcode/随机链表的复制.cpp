/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

// 思路： 顺序复制节点，方便随机查找。时间On，空间O1
// 1. 首先遍历链表，将每个节点复制一个同样val的节点放在该节点后面，只需要修改next指针保证每个节点后复制一个一样的新节点
// 2. 再次遍历链表，方便的为每个复制的节点找到random指针所指向的节点
// 3. 再次遍历链表，将复制的新节点摘出来，并恢复原链表

class Solution {
public:
    Node* copyRandomList(Node* head) {
        auto op = head;         //操作节点
        int n = 0;              //记录节点个数
        while(op) {             //遍历原链表的每个节点
            Node* cur_node = new Node(op->val);
            cur_node->next = op->next;  //在其后面复制一个val一样的节点，不考虑random指针
            op->next = cur_node;
            op = cur_node->next;        //只需要保证next指针连接
            ++ n;
        }

        op = head;
        while(op) {     //再次遍历链表
            auto cur_node = op->next;       //该节点遍历新复制的节点
            if(op->random == nullptr) {     //如果原链表中该节点的random指针指向null，则新节点同理
                cur_node->random = nullptr;
            } else {                        //否则，新节点指向原链表该节点的随机节点的下一个（顺序复制带来的好处）
                cur_node->random = op->random->next;
            }
            op = cur_node->next;
        }

        auto res = new Node(0);
        res->next = head;       //创建一个前置节点，方便删除节点
        head = res;
        while(n --) {           //需要摘出来n个新建节点
            auto del_node = head->next; //每次选中原始节点用于删除
            head->next = del_node->next;    //将原始节点摘出
            head = del_node->next;  //head每次指向新建的节点
            del_node->next = head->next;    //将原始节点的链恢复
        }
        return res->next;
    }
};