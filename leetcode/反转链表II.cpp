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

// 思路： 双指针法，时间On，空间O1，遍历一遍
// 1. 利用两个指针遍历需要更改的部分，防止断链，相对比较麻烦

class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if(left == right) return head;      //如果二者相等，表明无需反转任何部分
        auto res = new ListNode(0, head);   //建立虚拟头结点
        head = res;                         //重新设置头指针，方便头结点也需翻转的情况
        int first = left - 1;               //用于找到需要翻转的部分
        int cnt = right - left;             //用于确定需要翻转的部分是否已经全部翻转
        while(first --) {
            head = head->next;              //将head指向需要翻转的部分的前一个结点
        }
        auto first_node = head->next;       //用两个指针一一翻转结点
        auto second_node = first_node->next;
        while(cnt --) {                     //翻转left到right之间的结点
            auto next_node = second_node->next;     //用于记录结点，防止断链
            second_node->next = first_node;     //第二个节点回指
            first_node = second_node;       //更新两个节点，进行下一次翻转
            second_node = next_node;
        }
        head->next->next = second_node;     //将翻转部分的第一个结点的next指向翻转部分后的第一个结点
        head->next = first_node;            //将反转部分前的结点指向反转部分的最后一个结点
        return res->next;
    }
};