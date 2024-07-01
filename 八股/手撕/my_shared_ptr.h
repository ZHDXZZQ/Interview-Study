// 实现shared_ptr，后面可以补充weak_ptr和unique_ptr
#include <iostream>

// 模拟实现一个简化版的 shared_ptr

template <typename T>
class SharedPtr {
private:
    T* ptr;            // 指向对象的指针
    int* ref_count;    // 引用计数

public:
    // 构造函数
    explicit SharedPtr(T* p = nullptr) : ptr(p) {
        if (ptr) {
            ref_count = new int(1); // 初始化引用计数为1
        } else {
            ref_count = new int(0); // 若指针为空，则引用计数为0
        }
    }

    // 拷贝构造函数
    SharedPtr(const SharedPtr<T>& sp) : ptr(sp.ptr), ref_count(sp.ref_count) {
        if (ptr) {
            ++(*ref_count); // 拷贝时引用计数加1
        }
    }

    // 赋值运算符
    SharedPtr<T>& operator=(const SharedPtr<T>& sp) {
        if (this != &sp) { // 防止自我赋值
            // 先将当前对象的引用计数减1
            if (ptr && --(*ref_count) == 0) {
                delete ptr;
                delete ref_count;
            }
            // 复制新的对象
            ptr = sp.ptr;
            ref_count = sp.ref_count;
            if (ptr) {
                ++(*ref_count); // 新对象的引用计数加1
            }
        }
        return *this;
    }

    // 析构函数
    ~SharedPtr() {
        if (ptr && --(*ref_count) == 0) { // 如果引用计数为0，删除对象和引用计数
            delete ptr;
            delete ref_count;
        }
    }

    // 重载解引用操作符
    T& operator*() {
        return *ptr;
    }

    // 重载箭头操作符
    T* operator->() {
        return ptr;
    }

    // 获取引用计数
    int use_count() const {
        return *ref_count;
    }

    // 判断是否为空指针
    bool unique() const {
        return *ref_count == 1;
    }

    // 获取原始指针
    T* get() const {
        return ptr;
    }

    // 重置指针并释放当前对象
    void reset(T* p = nullptr) {
        if (ptr && --(*ref_count) == 0) {
            delete ptr;
            delete ref_count;
        }
        ptr = p;
        if (ptr) {
            ref_count = new int(1);
        } else {
            ref_count = new int(0);
        }
    }
};