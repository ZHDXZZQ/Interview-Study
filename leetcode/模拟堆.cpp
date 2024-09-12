/*
    思路： 添加堆中元素的双向映射，插入删除修改Ologn，查询O1
*/

#include <iostream>
#include <algorithm>
#include <string.h>

using namespace std;

const int N = 100010;

int h[N], ph[N], hp[N], cnt;
// h[N]: 存储堆元素的数组，最小堆结构。
// ph[N]: 位置映射数组，ph[i] 代表编号为 i 的插入序号在堆中的位置。
// hp[N]: 逆位置映射数组，hp[i] 代表堆中位置 i 对应的插入序号。
// cnt: 堆中当前元素的数量。
// m: 记录插入元素的顺序编号，用于对 ph 和 hp 的操作。

// 交换堆中两个元素的位置，更新堆数组 h 以及位置映射数组 ph 和 hp。
void heap_swap(int a, int b) {
    swap(ph[hp[a]], ph[hp[b]]);  // 更新位置映射数组 ph
    swap(hp[a], hp[b]);          // 更新逆位置映射数组 hp
    swap(h[a], h[b]);            // 交换堆数组 h 中的元素
}

// 自顶向下调整堆，保持最小堆的性质。u 为当前调整的节点位置。
// 比较 u 与它的两个子节点，如果有子节点比 u 小，则交换 u 和较小的子节点。
// 递归调整被交换的子节点位置。
void down(int u) {
    int t = u;  // 初始化 t 为当前节点 u
    if (u * 2 <= cnt && h[u * 2] < h[t]) {  // 如果左子节点存在且小于当前节点
        t = u * 2;  // 更新 t 为左子节点
    }
    if (u * 2 + 1 <= cnt && h[u * 2 + 1] < h[t]) {  // 如果右子节点存在且小于当前最小节点
        t = u * 2 + 1;  // 更新 t 为右子节点
    }
    if (u != t) {  // 如果当前节点不是最小的
        heap_swap(u, t);  // 交换当前节点与最小子节点
        down(t);  // 递归调整被交换的子节点
    }
}

// 自底向上调整堆，保持最小堆的性质。u 为当前调整的节点位置。
// 比较 u 与它的父节点，如果 u 小于父节点，则交换 u 和父节点位置。
// 持续更新，直到满足最小堆条件或者达到根节点。
void up(int u) {
    while (u / 2 && h[u] < h[u / 2]) {  // 当节点存在父节点且小于父节点时
        heap_swap(u, u / 2);  // 交换当前节点与父节点
        u >>= 1;  // 更新 u 为父节点的位置
    }
}


int main() {
    int n, m = 0;  // n: 操作数, m: 插入元素的序号
    scanf("%d", &n);  // 读取操作数
    while (n --) {  // 处理 n 个操作
        char op[5];  // 存储操作类型的字符串
        int k, x;  // k: 操作的元素编号, x: 操作的值
        scanf("%s", op);  // 读取操作类型
        if (!strcmp(op, "I")) {  // 插入操作
            scanf("%d", &x);  // 读取插入的值
            ++ cnt;  // 增加堆的元素计数
            ++ m;  // 增加插入序号
            ph[m] = cnt, hp[cnt] = m;  // 更新位置映射和逆位置映射
            h[cnt] = x;  // 插入元素到堆中
            up(cnt);  // 自底向上调整堆
        } else if (!strcmp(op, "PM")) {  // 查询最小值操作
            printf("%d\n", h[1]);  // 输出堆顶元素，即最小值
        } else if (!strcmp(op, "DM")) {  // 删除最小值操作
            heap_swap(1, cnt);  // 交换堆顶和最后一个元素
            -- cnt;  // 减少堆的元素计数
            down(1);  // 自顶向下调整堆
        } else if (!strcmp(op, "D")) {  // 删除任意元素操作
            scanf("%d", &k);  // 读取删除的元素编号
            k = ph[k];  // 获取元素在堆中的位置
            heap_swap(k, cnt);  // 交换指定元素与最后一个元素
            -- cnt;  // 减少堆的元素计数
            up(k);  // 自底向上调整
            down(k);  // 自顶向下调整
        } else {  // 修改任意元素操作
            scanf("%d%d", &k, &x);  // 读取修改的元素编号和新值
            k = ph[k];  // 获取元素在堆中的位置
            h[k] = x;  // 修改堆中元素的值
            up(k);  // 自底向上调整
            down(k);  // 自顶向下调整
        }
    }
    return 0;  // 程序结束
}