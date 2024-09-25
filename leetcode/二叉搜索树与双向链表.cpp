/*
    思路： 中序遍历，时间On，空间Ologn（递归栈空间）
    1. 利用二叉搜索树的特性，中序遍历即有序
    2. 利用递归的特性，根据前后顺序关系进行双向互指
*/

/*
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};*/
class Solution {
public:
	TreeNode* pre;
	void mid_order(TreeNode* p) {
		if (!p) {
			return;
		}
		mid_order(p->left); // 中序遍历，左中右
		if (pre != p) { // 如果相等，那是初始状态
			pre->right = p; // 一般状态下，pre是前一个结点，p是后一个节点，双向互指并更新pre，下一轮就还是前后的关系
			p->left = pre;
			pre = p;
		}
		mid_order(p->right);
	}
    TreeNode* Convert(TreeNode* pRootOfTree) {
        if (!pRootOfTree) {
			return nullptr;
		}
		pre = pRootOfTree;
		while (pre->left) {
			pre = pre->left;    // pre指向最左边的节点
		}
		TreeNode* res = pre;    // 最左边的节点就是返回双向链表的起点
		mid_order(pRootOfTree); // 对整个树做中序遍历
		return res;
    }
};
