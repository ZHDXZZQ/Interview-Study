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

// 思路： 双指针、翻转链表、合并，时间On，空间O1
// 1. 首先找到链表的中点，将链表后半部分翻转，然后依次插入即可

class Solution {
public:
    void reorderList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) { //特判，如果链表只有0或1个节点，无需重排
            return;
        }
        ListNode* slow = head;  //利用快慢指针迅速找到链表中点
        ListNode* fast = head;
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }   //假设有12345，5个节点，此时slow指向3；假设有1234个节点，此时slow指向2；因此slow的next就是后半个链表的开头，前半个链表要么和后半个链表等长，要么多一个
        ListNode* new_head = slow->next;
        ListNode* p = new_head;
        slow->next = nullptr;       //将前半链表脱离出来
        auto first = new_head;  //利用三个节点翻转后半段链表
        auto second = new_head->next;
        while (second) {        //翻转链表
            auto third = second->next;
            second->next = first;
            first = second;
            second = third;
        }
        new_head = first;       //此时原链表的尾巴节点即为后半链表翻转后的头节点
        p->next = nullptr;      //p为原先后半链表的头节点，现在是尾节点，将其置空
        while (new_head) {      //依次将后半链表插入前半链表中
            auto temp = head->next;
            auto new_temp = new_head->next;
            head->next = new_head;
            new_head->next = temp;
            new_head = new_temp;
            head = temp;
        }
        return;
    }
};