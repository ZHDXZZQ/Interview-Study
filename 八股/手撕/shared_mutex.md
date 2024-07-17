`std::shared_mutex` 是 C++17 引入的一种互斥类型，它允许多线程读写操作的高效并发控制。与传统的 `std::mutex` 不同，`std::shared_mutex` 提供了独占锁和共享锁两种锁定模式，这样可以实现读者-写者锁的功能，即允许多个线程同时读取数据，但在写操作时，确保只有一个线程可以写入数据，同时阻塞其他的读写操作。

### `std::shared_mutex` 的使用

#### 头文件
```cpp
#include <shared_mutex>
```

#### 成员函数
- `lock()`: 独占锁，阻塞其他读写操作。
- `unlock()`: 解锁独占锁或共享锁。
- `try_lock()`: 尝试获取独占锁，不阻塞。
- `lock_shared()`: 共享锁，阻塞写操作但不阻塞其他读操作。
- `unlock_shared()`: 解锁共享锁。
- `try_lock_shared()`: 尝试获取共享锁，不阻塞。

### 示例代码

以下是一个简单示例，演示如何使用 `std::shared_mutex` 来实现线程安全的读写操作：

```cpp
#include <iostream>
#include <shared_mutex>
#include <thread>
#include <vector>

class SharedData {
public:
    void write(int value) {
        std::unique_lock lock(mutex_);
        data_ = value;
        std::cout << "Written: " << value << std::endl;
    }

    int read() const {
        std::shared_lock lock(mutex_);
        std::cout << "Read: " << data_ << std::endl;
        return data_;
    }

private:
    mutable std::shared_mutex mutex_;
    int data_ = 0;
};

void reader(const SharedData& shared_data) {
    for (int i = 0; i < 5; ++i) {
        shared_data.read();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void writer(SharedData& shared_data) {
    for (int i = 0; i < 5; ++i) {
        shared_data.write(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    SharedData shared_data;

    std::thread writer_thread(writer, std::ref(shared_data));
    std::vector<std::thread> reader_threads;
    for (int i = 0; i < 3; ++i) {
        reader_threads.emplace_back(reader, std::cref(shared_data));
    }

    writer_thread.join();
    for (auto& thread : reader_threads) {
        thread.join();
    }

    return 0;
}
```

### 代码解释

1. **包含头文件**：
```cpp
#include <shared_mutex>
```

2. **共享数据类**：
```cpp
class SharedData {
public:
    void write(int value) {
        std::unique_lock lock(mutex_);
        data_ = value;
        std::cout << "Written: " << value << std::endl;
    }

    int read() const {
        std::shared_lock lock(mutex_);
        std::cout << "Read: " << data_ << std::endl;
        return data_;
    }

private:
    mutable std::shared_mutex mutex_;
    int data_ = 0;
};
```
- `SharedData` 类包含一个共享数据成员 `data_` 和一个 `std::shared_mutex` 类型的互斥量 `mutex_`。
- `write` 方法使用 `std::unique_lock` 对互斥量进行独占锁定，以保证写操作的独占性。
- `read` 方法使用 `std::shared_lock` 对互斥量进行共享锁定，以允许多个线程同时读取数据。

3. **读线程函数**：
```cpp
void reader(const SharedData& shared_data) {
    for (int i = 0; i < 5; ++i) {
        shared_data.read();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}
```

4. **写线程函数**：
```cpp
void writer(SharedData& shared_data) {
    for (int i = 0; i < 5; ++i) {
        shared_data.write(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
```

5. **主函数**：
```cpp
int main() {
    SharedData shared_data;

    std::thread writer_thread(writer, std::ref(shared_data));
    std::vector<std::thread> reader_threads;
    for (int i = 0; i < 3; ++i) {
        reader_threads.emplace_back(reader, std::cref(shared_data));
    }

    writer_thread.join();
    for (auto& thread : reader_threads) {
        thread.join();
    }

    return 0;
}
```
- 创建并启动一个写线程和多个读线程。
- 使用 `join` 方法等待所有线程完成。

### 另一种写法，不使用unique_lock
```C++
#include <iostream>
#include <shared_mutex>
#include <thread>
#include <vector>

class SharedData {
public:
    void write(int value) {
        mutex_.lock();  // 独占锁
        data_ = value;
        std::cout << "Written: " << value << std::endl;
        mutex_.unlock();  // 解锁
    }

    int read() const {
        mutex_.lock_shared();  // 共享锁
        std::cout << "Read: " << data_ << std::endl;
        int result = data_;
        mutex_.unlock_shared();  // 解锁共享锁
        return result;
    }

private:
    mutable std::shared_mutex mutex_;
    int data_ = 0;
};

void reader(const SharedData& shared_data) {
    for (int i = 0; i < 5; ++i) {
        shared_data.read();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void writer(SharedData& shared_data) {
    for (int i = 0; i < 5; ++i) {
        shared_data.write(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    SharedData shared_data;

    std::thread writer_thread(writer, std::ref(shared_data));
    std::vector<std::thread> reader_threads;
    for (int i = 0; i < 3; i++) {
        reader_threads.emplace_back(reader, std::cref(shared_data));
    }

    writer_thread.join();
    for (auto& thread : reader_threads) {
        thread.join();
    }

    return 0;
}

```

### 总结

`std::shared_mutex` 提供了一种有效的方式来管理多线程环境中的读写访问，通过共享锁和独占锁的组合，实现了高效的读写控制，特别适用于读多写少的场景。
通过直接使用 lock_shared 和 lock 进行显式锁定和解锁，可以实现线程安全的读写操作。尽管这种方法在代码中显得更为直观，但手动管理锁定和解锁可能会增加出错的风险，因此在复杂场景中仍然推荐使用 std::unique_lock 和 std::shared_lock 来自动管理锁的生命周期。