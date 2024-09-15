/*
    思路： 遍历，时间On，空间O1
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
    ListNode* deleteNode(ListNode* head, int val) {
        if (!head) {    // 如果链表没有节点，返回
            return head;
        }
        if (head->val == val) { // 如果要删除头节点，返回下一个节点
            return head->next;
        }
        auto temp = head;
        while (temp->next) {    // 遍历链表，利用前一个节点来判断下一个节点，方便删除
            if (temp->next->val == val) {   // 如果下一个节点要删除
                temp->next = temp->next->next;  // 删掉
                break;
            }
            temp = temp->next;  // 继续遍历下一个节点
        }
        return head;
    }
};