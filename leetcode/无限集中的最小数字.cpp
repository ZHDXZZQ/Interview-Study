/*
    思路： 模拟，时间Ologn，空间On
    具体看注释
*/

class SmallestInfiniteSet {
public:
    SmallestInfiniteSet() {
        smallest = 1;   // 初始化虚拟无限集当前最小值
    }
    
    int popSmallest() {
        if (smaller_set.empty()) {  // 如果实际无限集中没有数字
            int res = smallest; // 则当前最小值就是虚拟无限集的最小值
            ++ smallest;    // 这次弹出后，最小值+1
            return res;
        } else {
            int res = *smaller_set.begin(); // 否则的话有序实际无限集的开头就是当前最小值
            smaller_set.erase(res); // 将其弹出
            return res;
        }
    }
    
    void addBack(int num) {
        if (num < smallest) {   // 如果新插入数字小于虚拟无限集
            smaller_set.insert(num);    // 则记录下来，否则不用管
        }
    }

    int smallest;
    set<int> smaller_set;   // 存储无限集中实际上小于虚拟无限集的最小值
};

/**
 * Your SmallestInfiniteSet object will be instantiated and called as such:
 * SmallestInfiniteSet* obj = new SmallestInfiniteSet();
 * int param_1 = obj->popSmallest();
 * obj->addBack(num);
 */