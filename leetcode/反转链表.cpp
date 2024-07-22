/*
    思路： 双指针法，时间On，空间O1
    1. 利用两个指针遍历链表，将第二个指针指向前一个节点
    2. 利用第三个指针记录第二个指针的原next防止断链
    3. 全部翻转后，将原始头节点的next置空
*/

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
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (!head) {
            return nullptr;
        }
        auto old_head = head;
        auto first = head;
        auto second = first->next;
        while (second) {
            ListNode* third = second->next;
            second->next = first;
            first = second;
            second = third;
        }
        old_head->next = nullptr;
        return first;
    }
};