/*
    思路：中序遍历记录法，时间On，空间Ologn递归栈空间
    1. 用一个标志记录当前传入的节点，中序遍历过程中，如果碰到这个节点，记录下来
    2. 则下一个遍历到的节点就是目标节点

    优化思路：根据next节点爬树找，时间Ologn，空间O1
*/

// class Solution {
// public:
//     int flag = 0;   
//     struct TreeLinkNode* res;   // 返回值
//     struct TreeLinkNode* son;   // 记录给出的子树根节点

//     void bianli(TreeLinkNode* p){   // 中序遍历
//         if(p->left != NULL) {
//             bianli(p->left);
//         }
//         if(flag == 1) {     // flag==1  说明这个节点就是要输出的节点
//             res = p;   // 记录
//             flag = 0;   // 置flag为0  防止下一个节点更新掉当前节点
//         }
//         if(p == son) {
//             flag = 1;   // 如果当前节点是给出的节点，则表明下一个节点要输出，flag置1
//         }
//         if(p->right != NULL) {
//             bianli(p->right);
//         }
//         return ;
//     }

//     TreeLinkNode* GetNext(TreeLinkNode* pNode) {
//         son = pNode;
//         struct TreeLinkNode* root = pNode;
//         while(root->next != NULL) {
//             root = root->next;   //root用来找到根节点
//         }
//         bianli(root);
//         return res;
//     }
// };
// //递归方法时空复杂度都是On   如果要满足要求就考虑所有情况然后判断，不同情况找不同节点即可



// 优化思路，具体看注释
/*
struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;
    TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {
        
    }
};
*/
class Solution {
public:
    TreeLinkNode* GetNext(TreeLinkNode* pNode) {
        if (pNode == nullptr) {
            return nullptr;
        }
        if (pNode->right) { // 如果该节点有右孩子
            auto cur = pNode->right;
            while (cur->left) { // 找到右子树中的最左下节点
                cur = cur->left;
            }
            return cur;
        }
        auto father = pNode->next;  // 如果没有右孩子，就看父节点
        if (father && father->left == pNode) {  // 如果该节点是父节点的左孩子
            return father;  // 返回父节点
        }
        // 如果该节点是父节点的右孩子
        if (father && father->right == pNode) {
            auto up = father->next; // 一直向上
            auto cur = father;
            while (up && up->right == cur) {    // 要找到其某祖先节点是其父节点的左孩子为止
                cur = up;
                up = up->next;
            }
            if (up) {   // 如果up为空，那代表到根节点的父节点了，说明目标节点是中序遍历的最后一个节点，没有下一个了
                return up;  // 否则的话up节点就是结果
            }
        }
        // 如果是中序遍历的最后一个节点，返回空
        return NULL;        // #define NULL __null
    }
};
