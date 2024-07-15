/*
    思路： 快慢指针+反转链表，时间On，空间O1
    1. 本题的意思就是链表头和链表尾向中间前进，两两节点相加求最大和
    2. 因此找到中点，将后面反转，依次求和求最大值即可
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
    int pairSum(ListNode* head) {
        auto fast = head->next;     // 快慢指针找中点，对于偶数个节点的链表来说，快指针最终指向末尾节点
        auto slow = head;           // 慢指针最终指向前半截链表的末尾节点，即slow->next为后半段链表的头节点
        while (fast->next) {
            fast = fast->next->next;
            slow = slow->next;
        }
        auto first = slow->next;    // 利用first和second反转链表
        auto second = first->next;
        while (second) {
            auto tmp = second->next;    // 记录防止断链
            second->next = first;   // 依次向前指向
            first = second;
            second = tmp;
        }
        slow->next = nullptr;   // 将前半段尾巴置空
        long long res = 0;
        while (head && fast) {  // 遍历两半个链，fast为后半段的反转后的头节点
            long long sum = head->val + fast->val;
            res = max(res, sum);
            head = head->next;
            fast = fast->next;
        }
        return res;
    }
};