// 思路： 单调队列， 时间O1，空间On
// 1. 利用正常的队列维护购物车
// 2. 利用一个双端队列，规则配置为单调不递增，用来维护当前购物车的最大价值商品
// 3. 每次加入一个商品时，判断双端队列的尾部的价值，如果小于当前价值，则尾部出队，直到为空或者队尾价格大于等于当前商品价格，保证双端队列单调不递增。这样队头维护的就是最大价格的商品。
// 4. 每次出队时与双端队列队头判断，如果等于则说明当前出队的是最大价格的商品之一，则双端队列也要同步出队一个。否则的话正常出队，双端队列不动，这样双端队列的队头仍然是最大价格的商品。
// 5. 这样的话出队的商品如果价格不是最大价格商品，则不用管。

class Checkout {
public:
    Checkout() {}
    
    int get_max() {
        if (shoppint_cart.empty() || max_price_q.empty()) {
            return -1;  // 如果购物车为空，则返回-1
        }
        return max_price_q.front(); // 否则返回最大价格的商品价格
    }
    
    void add(int value) {
        shoppint_cart.push(value);  // 加入购物车
        while (max_price_q.size() && max_price_q.back() < value) {
            max_price_q.pop_back(); // 将队尾小于该价格的商品出队，直到队空
        }
        // 双端队列可以用add？
        max_price_q.push_back(value);   // 将该价格入到队尾，这就是当前一个最大价格出队后，该值就是当前情况的最大价值。
    }
    
    int remove() {
        if (shoppint_cart.empty()) {    // 如果队空，无法移出
            return -1;
        }
        int commodity = shoppint_cart.front();  // 否则的话移出队头商品
        shoppint_cart.pop();
        if (commodity == max_price_q.front()) { // 如果队头商品是当前最大价格
            max_price_q.pop_front();        // 最大价格跟着出队
        }
        return commodity;
    }

private:
    queue<int> shoppint_cart;
    deque<int> max_price_q; // 维护最大价格的双端队列，队头就是当前购物车内的最大价格
};

/**
 * Your Checkout object will be instantiated and called as such:
 * Checkout* obj = new Checkout();
 * int param_1 = obj->get_max();
 * obj->add(value);
 * int param_3 = obj->remove();
 */