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

/*
    思路： 计数器，时间On，空间O1
    1. 用一个计数器来记录当前遍历到第几个节点
    2. 将奇数节点和偶数节点分别插入到不同链表中，最后合并链表即可
*/

class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        ListNode* even = new ListNode();    // 偶数节点链表
        auto temp = even;
        ListNode* res = new ListNode(); // 奇数节点链表
        auto res_tmp = res;
        int i = 1;  // 计数器
        while (head) {
            if (i % 2 == 1) {   // 如果当前是奇数节点
                res_tmp->next = head;   // 插入到奇数链表中
                res_tmp = res_tmp->next;    
                head = head->next;  // 同步更新head
            } else {    // 偶数节点则插入到偶数链表
                temp->next = head;
                temp = temp->next;
                head = head->next;
            }
            ++ i;   // 计数器+1
        }
        temp->next = nullptr;   // 偶数链表结尾置空，避免成环
        res_tmp->next = even->next; // 将偶数链表接到奇数链表之后
        return res->next;
    }
};