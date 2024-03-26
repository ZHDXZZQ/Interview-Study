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

// 思路： 归并排序， 时间Onlogn，空间O1
// 1. 把所有节点分为多个归并段，归并段节点个数几何递增，第一次1个，然后2个，然后4个……
// 2. 归并段内保持有序，每次依次合并两个归并段，最终合并成一个链表
// 3. 然后再扩大归并段节点数量再进行归并
// 4. 知道归并段节点数量超过所有节点数量，则本次生成的链表全部有序
// 5. 具体流程看注释

class Solution {
public:
    ListNode* sortList(ListNode* head) {
        int node_cnt = 0;               //记录链表节点个数，方便归并时计算归并段的个数和节点数
        auto res = new ListNode(0, head);   //定义虚拟头节点作为实际头节点的前驱，方便操作
        while (head) {      //记录节点个数
            ++ node_cnt;
            head = head->next;
        }
        for (int i = 1; i < node_cnt; i *= 2) {        //i代表当前归并段的长度
            auto dummy = res;       //每轮归并结束，都要从头构造新链表，dummy每次重置为链表头节点的前驱节点，即虚拟头节点
            for (int j = 0; i + j < node_cnt; j += i * 2) { //j记录当前两个归并段左边归并段的位置，如果i+j超过了节点个数表示剩余节点数无法满足当前两个归并段左边归并段的个数，无需进行遍历，直接把左边归并段放在尾巴即可，因为每个归并段都是有序的，j每次加上当前两个归并段的个数，指向下一组归并段左边归并段的头节点的位置
                head = dummy->next; //head为当前两个归并段，左边归并段的头节点
                auto left_head = head;
                auto right_head = head; //指向当前两个归并段右边归并段的头节点
                for (int k = 0; k < i; ++ k) {  //能到这里表明左边归并段满足当前归并段个数，找到右边归并段的头节点
                    right_head = right_head->next;
                }
                int left = 0, right = 0;    //记录左右两个归并段分别加入链表的个数
                while (left < i && right < i && right_head) {   //只要有一边的归并段还没有归并完，且如果右边的归并段已经归并完（因为右边的归并段可能会数量少一些）则继续归并
                    if (left_head->val <= right_head->val) {    //选择小的插入虚拟头节点，虚拟头节点依次更新，然后更新当前归并段的头节点以及归并数量
                        dummy->next = left_head;
                        dummy = dummy->next;
                        left_head = left_head->next;
                        ++ left;
                    } else {
                        dummy->next = right_head;
                        dummy = dummy->next;
                        right_head = right_head->next;
                        ++ right;
                    }
                }   //到这里，两个归并段已经归并完成了一个，剩下一些有序节点，直接接到当前归并结果的后面即可
                while (left < i) {  //如果左边没有归并完，左边接到后面
                    dummy->next = left_head;
                    left_head = left_head->next;
                    dummy = dummy->next;
                    ++ left;
                }
                while (right < i && right_head) {   //如果右边没有归并完则接到后面，如果右边不够数量则也立即停止
                    dummy->next = right_head;
                    right_head = right_head->next;
                    dummy = dummy->next;
                    ++ right;
                }//此时dummy指向当前两个归并段的结尾，右边归并段的头节点已经指向了下一组归并段的左边归并段的头节点
                dummy->next = right_head;   //将本组归并段的结尾指向下一组归并段的左边归并段的头节点。对于下一组归并段来说，保持了dummy为当前归并段的头节点的前驱
            }
        }
        return res->next;
    }
};