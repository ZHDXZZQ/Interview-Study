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

// 思路： 多指针法，时间On，空间O1
// 1. 先统计链表长度，本质上本题是要将链表尾部的一些节点移到前面来，所以计算实际上需要将哪几个节点移到前面来
// 2. 找到需要移动的几个节点接到前面来即可

class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if(!head) return head;      //特判
        int n = 1;                  //统计链表长度
        auto tmp = head;            
        while(tmp -> next != NULL) {
            ++ n;
            tmp = tmp->next;
        }                           //统计完长度的同时，tmp指向了链表最后一个节点
        k %= n;                     //计算实际需要将后几个节点移动到前边来
        if(k == 0) return head;     //如果为0，则不移动
        k = n - k;                  //当前k的值为我们需要移动的部分的前边的部分的节点数
        auto node = head;           
        while(-- k) node = node->next;      //node节点此时指向需要移动的节点的前边的节点的尾节点，即新的尾节点
        auto new_head = node->next;     //新的头节点为node的下一个节点
        node->next = NULL;          //新的尾节点置空
        tmp->next = head;           //将原尾节点接到头节点之前
        return new_head;            //返回新的头节点即可
    }
};