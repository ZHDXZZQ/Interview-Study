/*
    实现一个简化版的 weak_ptr 主要包括以下步骤：

        实现 ControlBlock，用于管理引用计数。
        实现 shared_ptr，它能控制对象的生命周期，并记录引用计数。
        实现 weak_ptr，它能够引用 shared_ptr，但不会增加引用计数。
    
    ControlBlock：用来管理 shared_ptr 和 weak_ptr 的引用计数。shared_count 表示 shared_ptr 的数量，weak_count 表示 weak_ptr 的数量。

    shared_ptr：
    管理对象的生命周期，维护 ControlBlock 来追踪当前有多少 shared_ptr 正在使用对象。
    拥有标准的资源管理功能，如拷贝、赋值操作，以及引用计数的增加和减少。
    当 shared_ptr 的引用计数为 0 时，会销毁对象。

    weak_ptr：
    引用对象而不增加对象的引用计数，因此它不会影响对象的生命周期。
    提供 lock() 方法，尝试获取一个有效的 shared_ptr。如果对象已经销毁，lock() 返回一个空的 shared_ptr。
*/

#include <iostream>
using namespace std;

// 控制块，管理引用计数
class ControlBlock {
public:
    int shared_count;  // shared_ptr 引用计数
    int weak_count;    // weak_ptr 引用计数

    ControlBlock() : shared_count(1), weak_count(0) {}

    void add_shared() { shared_count++; }
    void release_shared() { shared_count--; }

    void add_weak() { weak_count++; }
    void release_weak() { weak_count--; }

    int get_shared_count() const { return shared_count; }
    int get_weak_count() const { return weak_count; }
};

// 简单的 shared_ptr 实现
template<typename T>
class weak_ptr;  // 前向声明

template<typename T>
class shared_ptr {
private:
    T* ptr;
    ControlBlock* control;

public:
    // 构造函数
    explicit shared_ptr(T* p = nullptr) : ptr(p) {
        if (ptr) {
            control = new ControlBlock();
        } else {
            control = nullptr;
        }
    }

    // 拷贝构造函数
    shared_ptr(const shared_ptr& other) : ptr(other.ptr), control(other.control) {
        if (control) {
            control->add_shared();
        }
    }

    // 析构函数
    ~shared_ptr() {
        release();
    }

    // 赋值操作符
    shared_ptr& operator=(const shared_ptr& other) {
        if (this != &other) {
            release();  // 释放当前资源
            ptr = other.ptr;
            control = other.control;
            if (control) {
                control->add_shared();
            }
        }
        return *this;
    }

    // 获取对象指针
    T* get() const {
        return ptr;
    }

    // 解引用操作符
    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

    // 获取引用计数
    int use_count() const {
        return control ? control->get_shared_count() : 0;
    }

    // 检查是否为空
    bool unique() const {
        return use_count() == 1;
    }

    // 释放资源
    void release() {
        if (control) {
            control->release_shared();
            if (control->get_shared_count() == 0) {
                delete ptr;
                if (control->get_weak_count() == 0) {
                    delete control;
                }
            }
        }
        ptr = nullptr;
        control = nullptr;
    }

    friend class weak_ptr<T>;  // weak_ptr 需要访问 shared_ptr 的私有成员
};

// 简单的 weak_ptr 实现
template<typename T>
class weak_ptr {
private:
    T* ptr;
    ControlBlock* control;

public:
    // 默认构造函数
    weak_ptr() : ptr(nullptr), control(nullptr) {}

    // 从 shared_ptr 构造
    weak_ptr(const shared_ptr<T>& sptr) : ptr(sptr.ptr), control(sptr.control) {
        if (control) {
            control->add_weak();
        }
    }

    // 拷贝构造函数
    weak_ptr(const weak_ptr& other) : ptr(other.ptr), control(other.control) {
        if (control) {
            control->add_weak();
        }
    }

    // 析构函数
    ~weak_ptr() {
        release();
    }

    // 赋值操作符
    weak_ptr& operator=(const weak_ptr& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            control = other.control;
            if (control) {
                control->add_weak();
            }
        }
        return *this;
    }

    // 锁定 weak_ptr，返回 shared_ptr
    shared_ptr<T> lock() const {
        if (control && control->get_shared_count() > 0) {
            return shared_ptr<T>(*this);
        } else {
            return shared_ptr<T>();  // 返回空的 shared_ptr
        }
    }

    // 释放资源
    void release() {
        if (control) {
            control->release_weak();
            if (control->get_shared_count() == 0 && control->get_weak_count() == 0) {
                delete control;
            }
        }
        ptr = nullptr;
        control = nullptr;
    }
};

int main() {
    shared_ptr<int> sp1(new int(10));
    weak_ptr<int> wp1(sp1);

    cout << "Shared count: " << sp1.use_count() << endl;  // 输出 1
    if (auto sp2 = wp1.lock()) {
        cout << "Locked value: " << *sp2 << endl;  // 输出 10
    } else {
        cout << "Unable to lock weak_ptr." << endl;
    }

    sp1.release();  // 释放 sp1

    if (auto sp2 = wp1.lock()) {
        cout << "Locked value: " << *sp2 << endl;
    } else {
        cout << "Unable to lock weak_ptr." << endl;  // 由于 sp1 已经释放，输出此行
    }

    return 0;
}
