/*
    auto_ptr 是 C++ 标准库中的一种智能指针，设计用于管理动态分配的对象，确保在对象超出作用域时自动释放内存。
    然而，由于它的一些设计缺陷，auto_ptr 已在 C++11 中被弃用，并被更为现代的智能指针（如 std::unique_ptr 和 std::shared_ptr）所取代。

    auto_ptr 使用所有权转移的方式管理资源。这意味着当一个 auto_ptr 被复制或赋值时，原指针会失去对资源的所有权，而新的指针会接管资源。
    这种行为导致了不明确的所有权管理，使其在某些场景下容易出错。
*/

/*
    在 C++98 中，auto_ptr 被设计为自动管理动态分配对象的生命周期，以避免内存泄漏。典型的使用场景包括：
        异常安全性：确保在异常抛出时，动态分配的对象能够自动释放，避免内存泄漏。
        简单的资源管理：在不需要复杂共享和引用计数的情况下，自动管理单一对象的生命周期。
    auto_ptr 的缺陷
        所有权转移：当 auto_ptr 被复制或赋值时，所有权会转移。这种行为容易导致潜在的错误，因为一个对象的生命周期可能被多个 auto_ptr 管理。
        不支持容器：由于所有权转移的特性，auto_ptr 不能安全地用于标准容器（如 std::vector 等），会导致未定义行为。
*/

/*
    替代方案：在 C++11 及以后，auto_ptr 被弃用，并由更为现代的智能指针取代：
        std::unique_ptr：独占所有权，不允许拷贝，但支持移动操作。
        std::shared_ptr：共享所有权，使用引用计数管理对象生命周期。
        std::weak_ptr：与 std::shared_ptr 配合使用，避免循环引用。
*/

#include <iostream>

// 简化版的auto_ptr
template<typename T>
class AutoPtr {
public:
    // 构造函数
    explicit AutoPtr(T* ptr = nullptr) : m_ptr(ptr) {}

    // 析构函数
    ~AutoPtr() {
        delete m_ptr;
    }

    // 拷贝构造函数 (转移所有权)
    AutoPtr(AutoPtr& other) : m_ptr(other.release()) {}

    // 拷贝赋值操作符 (转移所有权)
    AutoPtr& operator=(AutoPtr& other) {
        if (this != &other) {
            reset(other.release()); // 先释放当前资源，然后通过 release 函数转移所有权。
        }
        return *this;
    }

    // 获取指针
    T* get() const {
        return m_ptr;
    }

    // 释放内部指针的所有权，并返回指针
    T* release() {
        T* temp = m_ptr;
        m_ptr = nullptr;
        return temp;
    }

    // 重置内部指针，释放旧的资源。
    void reset(T* ptr = nullptr) {
        if (m_ptr != ptr) {
            delete m_ptr;
            m_ptr = ptr;
        }
    }

    // 重载 * 和 -> 操作符
    T& operator*() const {
        return *m_ptr;
    }

    T* operator->() const {
        return m_ptr;
    }

private:
    T* m_ptr; // 被管理的指针
};

int main() {
    AutoPtr<int> p1(new int(10));
    std::cout << *p1 << std::endl; // 输出 10

    AutoPtr<int> p2(p1); // p1 的所有权转移到 p2
    if (!p1.get()) {
        std::cout << "p1 is empty" << std::endl; // p1 现在为空
    }

    std::cout << *p2 << std::endl; // 输出 10

    AutoPtr<int> p3(new int(20));
    p2 = p3; // p3 的所有权转移到 p2，原来的 p2 资源被释放
    std::cout << *p2 << std::endl; // 输出 20

    return 0;
}
