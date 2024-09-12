/*
    思路： 前缀树，时间O32n，空间O32n，均为线性复杂度
    1. 利用二进制的0和1将数字拆分成前缀树，存储在叶节点，只要存在路径则必然会到叶节点找到这个数字
    2. 异或一定是从左往右，左边为1优先，这样最大
*/

#include <iostream>
#include <vector>

using namespace std;

class node {    // 前缀树节点
public:
    node* zero; // 下一位为0
    node* one;  // 下一位为1
    long long num;  // 叶子节点记录数字大小
    node() : zero(nullptr), one(nullptr), num(-1) {}
}*root;

void deleteTrie(node* root) {   // 析构用
    if (root == nullptr) return;
    deleteTrie(root->zero);
    deleteTrie(root->one);
    delete root;
}

int main() {
    root = new node();
    int n, x;
    cin >> n;
    vector<int> nums(n);    // 记录n个数字，方便一一比较
    auto temp = root;
    for (int a = 0; a < n; ++ a) {
        cin >> x;
        nums[a] = x;
        for (int i = 31; i >= 0; -- i) {    // 从左往右遍历32位二进制
            int b = ((x >> i) & 1);
            if (b == 0) {   // 如果是0
                if (!temp->zero) {  // 下一个为0的不存在，则新建一个
                    temp->zero = new node();
                }
                temp = temp->zero;  // 走到下一个为0的路径上
            } else if (b == 1) {    // 同理为1
                if (!temp->one) {
                    temp->one = new node();
                }
                temp = temp->one;
            }
        }
        temp->num = x;  // 此时指向叶节点，记录数字
        temp = root;    // 回到根节点，开启下一个数字的记录
    }
    int res = -1e9;
    for (int i = 0; i < n; ++ i) {
        int target = nums[i];   // 每次拿一个数找另一个匹配的数字
        for (int j = 31; j >= 0; -- j) {    // 从左找到右，直到叶节点
            int b = ((target >> j) & 1);
            if (b == 0) {   // 如果本位是0，则优先找1，这样异或值最大，且只有该节点存在，那么一定能走到底
                if (temp->one) {
                    temp = temp->one;
                } else {
                    temp = temp->zero;
                }
            } else if (b == 1) {    // 如果本位是1则优先找0
                if (temp->zero) {
                    temp = temp->zero;
                } else {
                    temp = temp->one;
                }
            }
        }
        int cur_res = target ^ temp->num;   // 将当前的最大情况求出
        res = max(res, cur_res);
        temp = root;    // 记得指回根，方便下一轮找
    }
    cout << res << endl;
    deleteTrie(root);
    return 0;
}