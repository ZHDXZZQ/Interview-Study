### `binary_semaphore` 介绍

`binary_semaphore` 是一种信号量实现，它类似于一个具有二值（0 和 1）的布尔量。`binary_semaphore` 用于在线程间进行简单的同步操作。它可以用来限制对共享资源的访问，确保某个时刻只有一个线程能够访问资源。

### 功能

1. **同步线程**：确保多个线程在特定的点上进行同步。
2. **保护共享资源**：限制对共享资源的访问，避免多个线程同时访问引发的数据竞争。

### 接口及使用

#### 创建与初始化

可以通过构造函数来创建一个 `binary_semaphore` 实例，并初始化它的计数值。

```cpp
#include <semaphore>
#include <iostream>
#include <thread>

std::binary_semaphore semaphore(1); // 初始计数值为1，表示资源可用

void task(int id) {
    semaphore.acquire(); // 获取信号量，计数值减1
    std::cout << "Thread " << id << " is running\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Thread " << id << " is done\n";
    semaphore.release(); // 释放信号量，计数值加1
}

int main() {
    std::thread t1(task, 1);
    std::thread t2(task, 2);

    t1.join();
    t2.join();

    return 0;
}
```

#### 接口

- **构造函数**

  `binary_semaphore(int initial_count)`：创建一个 `binary_semaphore` 实例，并设置初始计数值。

- **获取信号量**

  `void acquire()`：尝试获取信号量。如果计数值为 0，则线程将被阻塞，直到信号量可用（计数值变为 1）。

- **尝试获取信号量**

  `bool try_acquire()`：尝试获取信号量。如果成功，返回 `true`，否则返回 `false`。不会阻塞线程。

- **释放信号量**

  `void release()`：释放信号量，使计数值变为 1。如果有被阻塞的线程，则唤醒其中一个线程。

#### 示例

下面是一个简单的示例，展示如何使用 `binary_semaphore` 来保护共享资源。

```cpp
#include <semaphore>
#include <iostream>
#include <thread>
#include <vector>

std::binary_semaphore semaphore(1); // 初始计数值为1，表示资源可用

void task(int id) {
    semaphore.acquire(); // 获取信号量，计数值减1
    std::cout << "Thread " << id << " is running\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Thread " << id << " is done\n";
    semaphore.release(); // 释放信号量，计数值加1
}

int main() {
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(task, i);
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
```

在这个示例中，`binary_semaphore` 确保同一时间只有一个线程在运行 `task` 函数。其他线程在调用 `acquire` 时如果计数值为 0，将被阻塞，直到信号量被释放（即计数值变为 1）。

### 总结

- **同步线程**：通过 `acquire` 和 `release` 方法，可以方便地同步多个线程。
- **保护共享资源**：使用 `binary_semaphore` 可以保护共享资源，防止多个线程同时访问。
- **简化代码**：避免手动管理锁和条件变量的复杂性，提高代码的可读性和可维护性。

`binary_semaphore` 是 C++20 引入的一部分，提供了一种简单而高效的同步原语，适用于需要二值同步的场景。