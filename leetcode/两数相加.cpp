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

// 思路： 模拟，时间Omax（n，m），空间O1
// 1. 每位依次相加，需要考虑进位问题和某个链表更短的问题，具体看注释

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int CF = 0;             //进位标志
        ListNode* res = new ListNode(); //返回结果
        auto tmp = res;         //用于往结果中追加
        while(l1 || l2) {       //只要有一个链表还没有走完就继续走
            int num1 = 0;       //这两个数代表当前节点两个需要相加的数
            int num2 = 0;       //如果某个链表已经走完，则值为0，且不继续往后遍历节点
            if(l1 != NULL) {    //否则话则赋值并指向下一个节点
                num1 = l1->val;
                l1 = l1->next;
            }
            if(l2 != NULL) {
                num2 = l2->val;
                l2 = l2->next;
            }
            int cur = num1 + num2;      //当前位的和，如果有进位则+1
            if(CF == 1) ++ cur;
            if(cur >= 10)  {            //如果当前位大于10，则需要该进位标志
                CF = 1;                                     
                cur -= 10;              //并将当前位的和保留个位
            } else {
                CF = 0;
            }
            auto now_res = new ListNode(cur);   //构造当前位的节点
            tmp->next = now_res;                //放入结果中
            tmp = tmp->next;
        }
        if(CF == 1) {               //全部计算完之后如果还需要进位，则最高位置1
            tmp->next = new ListNode(1);
        }
        return res->next;
    }
};