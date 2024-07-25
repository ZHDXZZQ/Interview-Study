/*
    思路： dfs，时间On²，空间Ologn最坏的情况为On。优化可以用前缀和On，On
*/

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
class Solution {
public:
    unordered_set<TreeNode*> uset;  // 利用uset记录该节点是否被作为根节点计算过
    int res = 0;
    void dfs(TreeNode* t, int& targetSum, long long sum) {
        if (!t) {
            return;
        }        
        sum += t->val;  // 计算当前路径上的和
        if (sum == targetSum) { // 如果符合，则结果9=+1
            ++ res;
        }
        dfs(t->left, targetSum, sum);   // 利用当前和继续遍历子树
        dfs(t->right, targetSum, sum);
        if (uset.find(t->left) == uset.end()) { // 要判断子树是否已经作为根节点被计算过，否则会重复计算多次
            uset.insert(t->left);
            dfs(t->left, targetSum, 0); // 将该节点作为根节点继续计算子树
        }
        if (uset.find(t->right) == uset.end()) {
            uset.insert(t->right);
            dfs(t->right, targetSum, 0);
        }
    }

    int pathSum(TreeNode* root, int targetSum) {
        dfs(root, targetSum, 0);
        return res;
    }
};

--- 
// 以下为前缀和优化

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

typedef long long ll;

class Solution {
public:
    unordered_map<ll, int> rec;  //不用set是因为要考虑出现节点值为+0的情况，那就是一次性+多个结果
    int res = 0;

    int pathSum(TreeNode* root, int targetSum) {
        rec[0] ++;  //初始化0，如果sum==targetSum，即使没有0节点也是可以的
        dfs(root, 0, targetSum);
        return res;
    }

    void dfs(TreeNode* t, ll sum, int &tar) {
        if(!t) return;
        sum += t->val;  //算从根到现在节点的当前和
        res += rec[sum - tar];   //sum-tar代表超过的值，如果rec中有，证明有从根开始的某小段和等于sum-tar，那么减去那一小段，后面这一段也是连续的，且和==tar，相当于子树

        rec[sum] ++;  //把当前的和加入，dfs然后回溯
        dfs(t->left, sum, tar);
        dfs(t->right, sum, tar);
        rec[sum] --;

        return;
    }
};