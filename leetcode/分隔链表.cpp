/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

// 思路： 模拟，时间On，空间O1
// 1. 首先用一个指针记录插入位置，一个指针遍历全链表。指针都提前一个节点保留，方便移动
// 2. 插入位置前的节点一定都是小于x的，碰到后面的小于x的节点就插入到插入位置，并同步更新插入位置
// 3. 要考虑往头节点前面插的情况

class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        if(head == NULL) return NULL;           //特判
        auto ins_node = new ListNode(0, head);  //插入节点，构造在头节点之前，方便往头节点前插入新的节点
        head = ins_node;                        //头节点更新为刚构造的空节点
        while(ins_node->next != NULL && ins_node->next->val < x) {
            ins_node = ins_node->next;          //找到插入节点的位置，保证插入节点之前的节点的值都小于x
        }
        if(ins_node->next == NULL) return head->next;   //如果已经到队尾，则说明都是小于x的节点，无需改变
        auto tmp = ins_node->next;              //否则的话从插入节点后开始排查
        while(tmp -> next != NULL) {            //遍历链表
            if(tmp->next->val >= x) {           //如果下一个值大于等于x，继续遍历
                tmp = tmp->next;
            } else {        
                auto move_node = tmp->next;     //否则下一个节点要放到插入节点后
                tmp->next = move_node->next;    //将下一个节点放到插入节点后
                move_node->next = ins_node->next;
                ins_node->next = move_node;
                ins_node = ins_node->next;      //插入节点更新位置，遍历指针不变，因为下一个节点已经被移动了
            }
        }
        return head->next;
    }
};