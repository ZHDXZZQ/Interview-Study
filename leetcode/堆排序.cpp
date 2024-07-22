/*
    真实堆排序已经在算法模板中实现，这里直接使用优先队列。
    时间Onlogn，空间On
*/

#include <queue>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    int m, n;
    cin >> n >> m;
    priority_queue<int, vector<int>, greater<int>> heap;    // 小根堆
    while (n --) {
        int num;
        cin >> num;
        heap.push(num);
    }
    while (m --) {
        cout << heap.top() << " ";
        heap.pop();
    }
    return 0;
}