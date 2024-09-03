/*
    思路： 二叉哈夫曼树，时间Onlogn，空间On 堆排序的耗时
    1. 没有必要构建哈夫曼树
    2. 每次选择两个值最小的节点，进行组合生成一个新节点
*/

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    priority_queue<int, vector<int>, greater<int>> heap;
    while (n --) {
        int x;
        cin >> x;
        heap.push(x);
    }
    int res = 0;
    while (!heap.empty()) { // 哈夫曼树的合并过程
        int a = heap.top();
        heap.pop();
        if (heap.empty()) {
            break;
        }
        int b = heap.top();
        heap.pop();
        int new_node = a + b;
        heap.push(new_node);
        res += new_node;
    }
    cout << res;
    return 0;
}