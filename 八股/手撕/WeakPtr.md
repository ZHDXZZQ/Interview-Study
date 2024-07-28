// std::weak_ptr 是 C++11 标准库中的智能指针，它用于打破 std::shared_ptr 的循环引用问题，并提供一种非拥有型的对共享资源的访问方式。
// std::weak_ptr 不会增加对象的引用计数，因此不会阻止对象被销毁。
// 它主要用于观察 std::shared_ptr 管理的对象，但不控制对象的生命周期。
// 我们需要维护一个指向 shared_ptr 对象的弱引用，并且要能够从中获取原始的 shared_ptr。这涉及到引用计数和弱引用计数的管理。
// 作用：
// 解决循环引用：避免 std::shared_ptr 之间的循环引用问题，因为循环引用会导致内存泄漏。
// 观察性访问：允许观察一个对象而不阻止它的销毁。如果对象已被销毁，std::weak_ptr 将返回一个空的 std::shared_ptr。
// 缓存和延迟初始化：可以用于实现缓存机制，其中缓存对象可能会被释放，但缓存条目仍然有效直到对象被真正需要时。

`std::weak_ptr` 是 C++11 引入的智能指针，用于解决 `std::shared_ptr` 所带来的循环引用问题。它不控制对象的生命周期，但可以观察和访问由 `std::shared_ptr` 管理的对象。下面是 `std::weak_ptr` 的用法介绍和一些示例。

### 主要功能

1. **防止循环引用**：
   `std::weak_ptr` 不会增加引用计数，因此可以打破 `std::shared_ptr` 之间的循环引用。

2. **检查对象是否存在**：
   可以使用 `expired()` 方法检查对象是否已经被释放。

3. **安全访问对象**：
   通过 `lock()` 方法可以获取一个 `std::shared_ptr`，如果对象已被释放，则返回一个空的 `std::shared_ptr`。

### 主要接口

- **构造函数**：
  ```cpp
  std::weak_ptr<T> w;
  std::weak_ptr<T> w(shared_ptr<T> const& sp);
  ```

- **成员函数**：
  ```cpp
  bool expired() const noexcept; // 检查对象是否已经被释放
  shared_ptr<T> lock() const noexcept; // 获取一个 shared_ptr
  void reset() noexcept; // 释放对对象的引用
  ```

### 示例

#### 1. 防止循环引用
```cpp
#include <iostream>
#include <memory>

class Node {
public:
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev; // 使用 weak_ptr 防止循环引用

    ~Node() {
        std::cout << "Node destroyed" << std::endl;
    }
};

int main() {
    auto node1 = std::make_shared<Node>();
    auto node2 = std::make_shared<Node>();

    node1->next = node2;
    node2->prev = node1; // 使用 weak_ptr

    return 0;
    // 退出时 node1 和 node2 都能正常销毁
}
```

#### 2. 安全访问对象
```cpp
#include <iostream>
#include <memory>

class Object {
public:
    void show() {
        std::cout << "Object is alive" << std::endl;
    }
};

int main() {
    std::shared_ptr<Object> sp = std::make_shared<Object>();
    std::weak_ptr<Object> wp = sp;

    if (auto spt = wp.lock()) { // 获取 shared_ptr 并检查对象是否还存在
        spt->show();
    } else {
        std::cout << "Object is destroyed" << std::endl;
    }

    sp.reset(); // 释放 shared_ptr 所管理的对象

    if (auto spt = wp.lock()) {
        spt->show();
    } else {
        std::cout << "Object is destroyed" << std::endl;
    }

    return 0;
}
```

### 总结

`std::weak_ptr` 是一种辅助智能指针，用于观察但不管理对象的生命周期，主要用于解决 `std::shared_ptr` 的循环引用问题。通过 `expired()` 和 `lock()` 方法，`std::weak_ptr` 提供了一种安全访问对象的机制，同时避免了循环引用带来的内存泄漏。