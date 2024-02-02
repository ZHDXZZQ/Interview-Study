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

// 思路： 双指针法，时间Om+n，空间O1
// 1. 两个指针从两个链表依次比较，因为非递减，因此每次把小的节点接到结果中
// 2. 如果某一个链表遍历完了，直接把另一个链表剩余的节点接到后面即可

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if (list1 == NULL) return list2;        //如果有某个链表为空，返回另一个链表的头节点即可
        else if (list2 == NULL) return list1;
        else if (!list1 && !list2) return NULL;
        ListNode* res = new ListNode();     //这里必须得声明new
        auto tmp = res;                     //用于遍历
        while(list1 && list2) {             //当两个链表都没有遍历完时
            if(list1->val > list2->val) { 
                tmp->next = list2;          //把更小的节点接进去
                tmp = tmp->next;            //更新tmp和list2所指的节点
                list2 = list2->next;
            } else {
                tmp->next = list1;          //同理
                tmp = tmp->next;
                list1 = list1->next;
            }
        }
        if(list1 == NULL) {                 //循环结束后一定还有一个链表没有接完
            tmp->next = list2;              //直接把剩下的链表接到后面即可
        } else {
            tmp->next = list1;
        }
        return res->next;
    }
};