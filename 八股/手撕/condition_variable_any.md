`condition_variable` 和 `condition_variable_any` 都是 C++ 标准库中的同步原语，用于实现线程间的等待和通知机制。它们的主要区别在于与锁的兼容性和使用灵活性。
`condition_variable_any` 是 C++ 标准库中的同步原语，提供了一种线程间的通知机制。它允许一个线程等待一个条件变量，而另一个线程可以通知等待的线程，条件满足时被唤醒。`condition_variable_any` 与 `condition_variable` 类似，但它可以与任何符合 Lockable 要求的锁一起使用，而不仅限于 `std::unique_lock<std::mutex>`。

### `condition_variable` 和 `condition_variable_any` 的区别

1. **锁的兼容性**：
   - `condition_variable` 只能与 `std::unique_lock<std::mutex>` 一起使用。
   - `condition_variable_any` 可以与任何满足 Lockable 要求的锁一起使用，例如 `std::unique_lock<std::shared_mutex>`，`std::lock_guard<std::mutex>` 等。

2. **性能**：
   - `condition_variable` 在某些情况下可能会比 `condition_variable_any` 更高效，因为它的实现可以更优化，专门针对 `std::unique_lock<std::mutex>` 进行调优。
   - `condition_variable_any` 更灵活，但由于其通用性，可能在性能上稍逊于 `condition_variable`。

### 具体示例

#### 使用 `condition_variable` 的代码

```cpp
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
#include <iostream>

std::queue<int> dataQueue;
std::mutex mtx;
std::condition_variable cv;

void producer() {
    for (int i = 0; i < 10; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::lock_guard<std::mutex> lock(mtx);
        dataQueue.push(i);
        std::cout << "Produced: " << i << std::endl;
        cv.notify_one();
    }
}

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !dataQueue.empty(); });
        int data = dataQueue.front();
        dataQueue.pop();
        std::cout << "Consumed: " << data << std::endl;
        lock.unlock();
        if (data == 9) break;  // 结束条件
    }
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}
```

#### 使用 `condition_variable_any` 的代码

```cpp
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
#include <iostream>

std::queue<int> dataQueue;
std::mutex mtx;
std::condition_variable_any cv;

void producer() {
    for (int i = 0; i < 10; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::lock_guard<std::mutex> lock(mtx);
        dataQueue.push(i);
        std::cout << "Produced: " << i << std::endl;
        cv.notify_one();
    }
}

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !dataQueue.empty(); });
        int data = dataQueue.front();
        dataQueue.pop();
        std::cout << "Consumed: " << data << std::endl;
        lock.unlock();
        if (data == 9) break;  // 结束条件
    }
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}
```

#### 接口

- **构造函数**

  `condition_variable_any()`：创建一个 `condition_variable_any` 对象。

- **等待**

  `void wait(Lock& lock)`：等待另一个线程调用 `notify_one` 或 `notify_all`，并且重新获取锁。`lock` 必须是一个满足 Lockable 要求的对象。
  
  `void wait(Lock& lock, Predicate pred)`：等待另一个线程调用 `notify_one` 或 `notify_all`，并且 `pred` 返回 `true`。`pred` 是一个可调用对象，当 `pred` 返回 `true` 时，等待结束。

- **通知**

  `void notify_one()`：唤醒等待该条件变量的一个线程。
  
  `void notify_all()`：唤醒等待该条件变量的所有线程。


### `condition_variable_any` 的优势

1. **灵活性**：
   - `condition_variable_any` 允许与任何满足 Lockable 要求的锁一起使用，这使得它在需要使用不同类型的锁时更为灵活。例如，可以与 `std::shared_mutex` 一起使用，从而支持读写锁的场景。

2. **更广泛的适用性**：
   - 在某些复杂的多线程应用场景中，可能需要不同类型的锁来协调线程间的同步，而 `condition_variable_any` 的通用性使得它能够适应这些需求。

### 适用场景

- **`condition_variable`**：
  - 当使用简单的互斥锁 (`std::mutex`) 进行线程同步时，`condition_variable` 是一个性能较高的选择。
  - 在需要高性能且锁类型固定的场景下，优先选择 `condition_variable`。

- **`condition_variable_any`**：
  - 当需要使用多种类型的锁（如 `std::shared_mutex`）进行同步时，`condition_variable_any` 提供了更大的灵活性。
  - 在复杂的同步场景中，需要使用不同类型的锁来协调线程操作时，选择 `condition_variable_any`。

总结来说，`condition_variable_any` 提供了更大的灵活性，能够与任何符合 Lockable 要求的锁一起使用，而 `condition_variable` 则在性能上可能更优，但只能与 `std::unique_lock<std::mutex>` 一起使用。根据具体应用场景选择合适的同步原语，可以实现更高效、更灵活的线程同步。