/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

// 思路：面向对象编程OOP，实现一个类，时间On，空间On，后续调用方法的时间为O1
// 1. 按照要求实现功能，只需要记录二叉搜索树的中序遍历结果，以及当前访问的位置

class BSTIterator {
public:
    void mid_order(TreeNode* t) {       //中序遍历，不再赘述
        if(!t) { return; }
        mid_order(t->left);
        mid_order_res.push_back(t->val);
        mid_order(t->right); 
    }

    BSTIterator(TreeNode* root) {       //构造函数
        mid_order(root);                //将树进行中序遍历，结果插入成员变量
        size = mid_order_res.size();    //记录树的节点个数
    }
    
    int next() {                        //next函数，先将指针+1，再取出该位置的值
        ++ pointer;
        return mid_order_res[pointer];
    }
    
    bool hasNext() {                    //判断是否有next
        if (pointer == size - 1) {      //如果当前指针已经指向尾结点，则返回false
            return false;
        } else {
            return true;                //其余情况都还有下一个结点
        }
    }

private:                            //一般来说，类的成员遍历以private类型放在类的最后，前面是方便外界调用的成员方法
    vector<int> mid_order_res;      //存储中序遍历结果
    int pointer = -1;               //记录当前指针所指的位置，初始化为所有结点的前一个
    int size = 0;                   //记录树的结点数量，这里可以不需要
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */