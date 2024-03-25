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

// 思路： 模拟， 时间On，空间O1
// 1. 本题可以拆成多次进行翻转一组链表，只需额外记录上下组的头尾节点以防断链
// 2. 具体看注释

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (k == 1) { return head; }        //如果每一个为1组，无需翻转
        auto res = new ListNode();          //建立虚拟头节点，用于返回答案，方便后续遍历
        res->next = head;                   //虚拟头节点的next指向真正的头节点，方便后续使用
        auto last = res;                    //last表示上一组的最后一个节点
        while (head) {                      //只要当前组的头节点不为空则继续，如果为空则表示恰好翻转了n组节点，每组k个
            auto tail = head;               //tail用于标记当前组的尾节点的位置
            for (int i = 1; i < k; ++ i) {  
                tail = tail->next;          //tail找到尾节点
                if (tail == nullptr) {      //如果找寻途中tail就越界，说明该组不够k个节点，直接返回，该组不翻转
                    return res->next;
                }
            }
            auto next_head = tail->next;    //当前tail指向该组的尾节点，next head指向下一组的头节点
            auto first = head, second = first->next;    //该组至少有两个节点，一一遍历
            for (int i = 1; i < k; ++ i) {
                auto third = second->next;  //第三个节点仅仅作为记录使用，防止翻转过程断链，不会改变第三节点的指针，因为过程中第三节点可能已到达下组
                second->next = first;       //第二个节点指向第一个节点
                first = second;             //然后顺移，将该组除头节点外的全部的节点都指向前一个节点，此时头节点还是指向第二个节点
                second = third;
            }
            head->next = next_head;         //此时，该组原本的头节点成为了尾节点，指向下一组的头节点
            last->next = tail;              //该组的尾节点成为了头节点，被上一组的尾节点指向
            last = head;                    //更新该组尾节点为下一组的上组的尾节点
            head = next_head;               //更新下一组的头节点
        }
        return res->next;
    }
};