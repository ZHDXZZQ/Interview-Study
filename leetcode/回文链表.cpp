/*
    思路： 快慢指针+翻转链表，时间On，空间O1
    1. 先找到中间节点
    2. 翻转后半部分链表
    3. 一次比较节点是否相同
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
    ListNode* rever_list(ListNode* head) {  // 递归的方法翻转链表
        if (!head) { return nullptr; }
        auto first = head;
        auto second = head->next;
        while (second) {
            auto third = second->next;
            second->next = first;
            first = second;
            second = third;
        }
        head->next = nullptr;
        return first;
    }

    bool isPalindrome(ListNode* head) {
        auto fast = head;
        auto slow = head;
        while (fast->next && fast->next->next) {    // 快慢指针找到中间节点
            fast = fast->next->next;
            slow = slow->next;
        }
        auto new_head = rever_list(slow->next); // 慢指针的next就是后半部分的开头，无论是奇数还是偶数，翻转后半部分链表
        while (new_head && head) {  // 前面长度相同的部分判断是否相等
            if (new_head->val != head->val) {   // 有不相等的就不是，否则就是
                return false;
            }
            new_head = new_head->next;  // 有个疑问，为什么不加这两句对于示例1不是死循环而是返回false？
            head = head->next;
        }
        return true;
    }
};