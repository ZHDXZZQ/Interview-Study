/*
    思路： 模拟，时间On1*n2，空间Oh1，其中h1表示树1的高度
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
	bool is_same(TreeNode* pRoot1, TreeNode*pRoot2) {
		if (!pRoot2) {  // 如果子结构节点指空了，无论树1是否还有节点，表示这个分支判断完成，匹配
			return true;
		}
		if (!pRoot1 && pRoot2) {    // 否则的话，如果子结构还每判断完，树1就空了，不匹配
			return false;
		}
		if (pRoot1->val == pRoot2->val) {   // 都有节点时则的判断值是否相同，相同的话在一起看子节点
			return is_same(pRoot1->left, pRoot2->left) && is_same(pRoot1->right, pRoot2->right);
		}
		return false;   // 值不同则不匹配
	}

    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2) {
		if (!pRoot1 || !pRoot2) {   // 双方只要有一个为空，则不是子结构
			return false;
		}
        // 否则判断这两个根的树是否是相同的，以及树1的两个子树是否相同
		return is_same(pRoot1, pRoot2) || HasSubtree(pRoot1->left, pRoot2) || HasSubtree(pRoot1->right, pRoot2);
    }
};
