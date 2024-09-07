// 使用了多个固定大小的缓冲区（blocks）来模拟 std::deque 的存储策略。
// 真实的deque采用双向链表管理多个缓冲区

#include <iostream>
#include <stdexcept>
#include <vector>

template <typename T>
class Deque {
public:
    Deque() : num_blocks_(0), front_block_(0), back_block_(0), front_index_(0), back_index_(0) {
        allocate_block();
    }

    ~Deque() {
        for (auto block : blocks_) {
            delete[] block;
        }
    }

    // 插入到前面
    void push_front(const T& value) {
        if (front_index_ == 0) {    // 到头了
            allocate_block();   // 申请
            front_block_--; // 指向头部缓冲区
            front_index_ = block_size_ - 1; // 指向当前头部缓冲区的下标
        } else {
            front_index_--;
        }
        blocks_[front_block_][front_index_] = value;
    }

    // 插入到后面
    void push_back(const T& value) {
        if (back_index_ == block_size_) {   // 最后一个缓冲区满了
            allocate_block();   // 申请新的缓冲区
            back_block_++;      // 指向最后一个缓冲区
            back_index_ = 0;    // 指向最后一个缓冲区当前的下标
        }
        blocks_[back_block_][back_index_] = value;
        back_index_++;  // 下标++
    }

    // 从前面移除
    void pop_front() {
        if (is_empty()) {
            throw std::out_of_range("Deque is empty");
        }
        if (front_index_ == block_size_ - 1) {  // 如果已经指向当前缓冲区的尾部
            delete[] blocks_[front_block_]; // 析构该缓冲区
            blocks_.erase(blocks_.begin() + front_block_);  // 删掉这个缓冲区，vector的erase函数
            num_blocks_--;  // 缓冲区数量-1
            front_block_++; // 头部缓冲区是下一个
            front_index_ = 0;   // 索引从头开始
        } else {
            front_index_++;
        }
    }

    // 从后面移除
    void pop_back() {
        if (is_empty()) {
            throw std::out_of_range("Deque is empty");
        }
        if (back_index_ == 0) { // 如果最后一个缓冲区空了
            delete[] blocks_[back_block_];  // 析构掉
            blocks_.pop_back(); // 弹出
            num_blocks_--;  // 缓冲区-1
            back_block_--;  // 尾部缓冲区为前一个
            back_index_ = block_size_;  // 下标指向尾部
        } else {
            back_index_--;
        }
    }

    // 访问前面元素
    T& front() {
        if (is_empty()) {
            throw std::out_of_range("Deque is empty");
        }
        return blocks_[front_block_][front_index_];
    }

    // 访问后面元素
    T& back() {
        if (is_empty()) {
            throw std::out_of_range("Deque is empty");
        }
        return blocks_[back_block_][back_index_ - 1];
    }

    // 获取大小
    size_t size() const {
        return (back_block_ - front_block_ - 1) * block_size_ + back_index_ + block_size_ - front_index_;
    }

    // 检查是否为空
    bool is_empty() const {
        return size() == 0;
    }

private:
    static const size_t block_size_ = 10; // 每个缓冲区的大小
    size_t num_blocks_; // 缓冲区个数
    size_t front_block_;    // 头缓冲区下标
    size_t back_block_;     // 尾缓冲区下标
    size_t front_index_;    // 当前查询的缓冲区的头部索引   
    size_t back_index_;     // 当前查询的缓冲区的尾部索引
    std::vector<T*> blocks_;    // 所有缓冲区，真实的deque使用的是双向链表

    void allocate_block() { // 申请一个缓冲区
        blocks_.push_back(new T[block_size_]);
        ++ num_blocks_;
    }
};

int main() {
    Deque<int> dq;

    dq.push_back(1);
    dq.push_back(2);
    dq.push_front(0);

    std::cout << "Front: " << dq.front() << std::endl; // Output: 0
    std::cout << "Back: " << dq.back() << std::endl;   // Output: 2

    dq.pop_front();
    dq.pop_back();

    std::cout << "Front: " << dq.front() << std::endl; // Output: 1

    return 0;
}
