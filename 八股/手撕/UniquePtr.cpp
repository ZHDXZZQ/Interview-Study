// 支持move语义，没有专门处理数组的申请和删除
#include <iostream>

template<typename T>
class UniquePtr {
private:
    T* ptr;

public:
    // 构造函数
    explicit UniquePtr(T* p = nullptr) : ptr(p) {}

    // 析构函数
    ~UniquePtr() {
        delete ptr;
    }

    // 禁止拷贝构造
    UniquePtr(const UniquePtr&) = delete;

    // 禁止拷贝赋值操作
    UniquePtr& operator=(const UniquePtr&) = delete;

    // 移动构造函数
    UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    // 移动赋值操作
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    // 重载 * 操作符
    T& operator*() const {
        return *ptr;
    }

    // 重载 -> 操作符
    T* operator->() const {
        return ptr;
    }

    // 获取指针
    T* get() const {
        return ptr;
    }

    // 释放所有权
    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    // 重置指针
    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }
};

// 示例使用
int main() {
    UniquePtr<int> up1(new int(10));
    std::cout << "up1 value: " << *up1 << std::endl;

    // 移动构造
    UniquePtr<int> up2(std::move(up1));
    std::cout << "up2 value: " << *up2 << std::endl;

    // up1 现在为空
    if (up1.get() == nullptr) {
        std::cout << "up1 is now nullptr" << std::endl;
    }

    // 移动赋值操作
    UniquePtr<int> up3;
    up3 = std::move(up2);
    std::cout << "up3 value: " << *up3 << std::endl;

    // up2 现在为空
    if (up2.get() == nullptr) {
        std::cout << "up2 is now nullptr" << std::endl;
    }

    return 0;
}
