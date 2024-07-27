/*
    思路： 链表对齐，时间On+m，空间O1
    1. 先计算出两个链表的长度
    2. 然后将两个链表尾部对齐，将更长的链表的头指针移动，直到两个链表当前的剩余长度相等
    3. 一起往后遍历，如果两个链表相交，就会碰到相同的节点
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int len_a = 0;
        int len_b = 0;
        auto tmp = headA;
        while (tmp) {   // 统计两个链表的长度
            tmp = tmp->next;
            ++ len_a;
        }
        tmp = headB;
        while (tmp) {
            tmp = tmp->next;
            ++ len_b;
        }
        while (len_a > len_b) { // 将长链表的头指针往后移动，保证新的子链表和另一个链表长度相等
            headA = headA->next;
            -- len_a;
        }
        while (len_b > len_a) {
            headB = headB->next;
            -- len_b;
        }
        while (headA && headB && headA != headB) {  // 一起往后移动
            headA = headA->next;
            headB = headB->next;
        }
        if (headA == nullptr || headB == nullptr) { // 如果移动到末尾还没有相遇，则不相交
            return nullptr;
        }
        return headA;   // 否则相交，且此时相交部分是同一个节点
    }
};