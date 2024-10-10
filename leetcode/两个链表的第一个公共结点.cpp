/*
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};*/

/*
    思路： 遍历，时间On，空间O1
    两个链表尾对齐，找到第一个相同的节点，如果没有则返回空
*/

class Solution {
public:
    ListNode* FindFirstCommonNode(ListNode* pHead1, ListNode* pHead2) {
        int len_1 = 0, len_2 = 0;   // 记录链表1和2的长度
		auto tmp = pHead1;
		while (tmp) {
			tmp = tmp->next;
			++ len_1;
		}
		tmp = pHead2;
		while (tmp) {
			tmp = tmp->next;
			++ len_2;
		}

		if (len_1 > len_2) {    // 将两个链表尾对齐，长的那个链表的头节点往后移动，直到剩余的长度和短链表长度相同
			auto gap = len_1 - len_2;
			while (gap) {
				pHead1 = pHead1->next;
				-- gap;
			}
		} else if (len_1 < len_2) {
			auto gap = len_2 - len_1;
			while (gap) {
				pHead2 = pHead2->next;
				-- gap;
			}
		}

        // 两个链表一起往后找，因为此时后面的长度是相同的，如果有公共的尾部，则会找到公共部分的起点，如果没有，则会一起遍历完全
		while (pHead1 && pHead2 && pHead1 != pHead2) {
			pHead1 = pHead1->next;
			pHead2 = pHead2->next;
		}
		return pHead1;
    }
};
