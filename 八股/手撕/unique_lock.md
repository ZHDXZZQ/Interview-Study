`std::unique_lock` 是 C++ 标准库中的一个模板类，用于管理锁对象。与 `std::lock_guard` 相比，它提供了更灵活的锁定机制。`std::unique_lock` 可以锁定、解锁和延迟锁定，非常适用于需要复杂锁定逻辑的场景。和lock_guard的相同点就是其也会在生命周期结束时自动析构并释放锁，避免了异常造成的死锁。

### `std::unique_lock` 的主要功能

1. **灵活的锁管理**：`std::unique_lock` 可以在构造时不立即锁定，而是在需要时再锁定。
2. **延迟锁定**：可以在创建 `std::unique_lock` 对象后，延迟锁定操作。
3. **显式解锁和重新锁定**：可以显式地解锁和重新锁定。
4. **移动语义**：`std::unique_lock` 支持移动语义，可以在不同的作用域间移动。

### 使用方法

#### 1. 基本使用方法

`std::unique_lock` 可以通过构造函数立即锁定互斥量：
```cpp
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;

void thread_function() {
    std::unique_lock<std::mutex> lock(mtx); // 立即锁定
    std::cout << "Thread " << std::this_thread::get_id() << " has locked the mutex." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1)); // 模拟工作
}

int main() {
    std::thread t1(thread_function);
    std::thread t2(thread_function);

    t1.join();
    t2.join();

    return 0;
}
```

#### 2. 延迟锁定

可以通过延迟锁定机制在构造时不立即锁定互斥量，而是在需要时调用 `lock` 方法：
```cpp
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;

void thread_function() {
    std::unique_lock<std::mutex> lock(mtx, std::defer_lock); // 延迟锁定
    std::cout << "Thread " << std::this_thread::get_id() << " created the unique_lock." << std::endl;

    // 一些操作

    lock.lock(); // 在需要时显式锁定
    std::cout << "Thread " << std::this_thread::get_id() << " has locked the mutex." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1)); // 模拟工作
}

int main() {
    std::thread t1(thread_function);
    std::thread t2(thread_function);

    t1.join();
    t2.join();

    return 0;
}
```

#### 3. 显式解锁和重新锁定

可以显式地解锁和重新锁定：
```cpp
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;

void thread_function() {
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << "Thread " << std::this_thread::get_id() << " has locked the mutex." << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1)); // 模拟工作

    lock.unlock(); // 显式解锁
    std::cout << "Thread " << std::this_thread::get_id() << " has unlocked the mutex." << std::endl;

    // 一些操作

    lock.lock(); // 重新锁定
    std::cout << "Thread " << std::this_thread::get_id() << " has relocked the mutex." << std::endl;
}

int main() {
    std::thread t1(thread_function);
    std::thread t2(thread_function);

    t1.join();
    t2.join();

    return 0;
}
```

#### 4. 使用 `try_lock` 尝试锁定

可以尝试锁定互斥量，而不是阻塞等待锁定：
```cpp
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;

void thread_function() {
    std::unique_lock<std::mutex> lock(mtx, std::try_to_lock);
    if (lock.owns_lock()) {
        std::cout << "Thread " << std::this_thread::get_id() << " has locked the mutex." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); // 模拟工作
    } else {
        std::cout << "Thread " << std::this_thread::get_id() << " failed to lock the mutex." << std::endl;
    }
}

int main() {
    std::thread t1(thread_function);
    std::thread t2(thread_function);

    t1.join();
    t2.join();

    return 0;
}
```

#### 5. 移动语义move
移动语义是 C++11 引入的一种机制，用于高效地转移资源所有权，避免不必要的复制操作。`std::unique_lock` 支持移动语义，这意味着一个 `std::unique_lock` 对象可以将其锁所有权转移给另一个 `std::unique_lock` 对象。

以下是一个使用 `std::unique_lock` 的移动语义的示例：

```cpp
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;

void thread_function(std::unique_lock<std::mutex> lock) {
    if (lock.owns_lock()) {
        std::cout << "Thread " << std::this_thread::get_id() << " has locked the mutex." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); // 模拟工作
    }
}

int main() {
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << "Main thread has locked the mutex." << std::endl;

    // 将锁转移给另一个线程
    std::thread t(thread_function, std::move(lock));

    t.join();

    if (!lock.owns_lock()) {
        std::cout << "Main thread no longer owns the lock." << std::endl;
    }

    return 0;
}
```

通过这个示例，可以看到 `std::unique_lock` 的移动语义如何在多线程编程中高效地管理锁的所有权。使用 `std::move` 将 `std::unique_lock` 对象的所有权转移给另一个线程，可以避免不必要的锁复制和资源浪费，从而提高程序的性能。

#### 6. owns_lock
`owns_lock` 是 `std::unique_lock` 类的一个成员函数，它用于检查当前 `std::unique_lock` 对象是否拥有所管理的互斥锁。
```cpp
bool owns_lock() const noexcept;
```

该方法返回一个布尔值：
- 如果当前 `std::unique_lock` 对象拥有互斥锁，返回 `true`。
- 如果当前 `std::unique_lock` 对象不拥有互斥锁，返回 `false`。

```cpp
#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;

void thread_function() {
    std::unique_lock<std::mutex> lock(mtx);
    if (lock.owns_lock()) {
        std::cout << "Thread " << std::this_thread::get_id() << " has locked the mutex." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); // 模拟工作
    }
}

int main() {
    std::unique_lock<std::mutex> lock(mtx);
    if (lock.owns_lock()) {
        std::cout << "Main thread has locked the mutex." << std::endl;
    }

    // 创建一个新的线程
    std::thread t(thread_function);

    // 将锁所有权转移给另一个线程
    lock.unlock();
    if (!lock.owns_lock()) {
        std::cout << "Main thread no longer owns the lock." << std::endl;
    }

    t.join();

    return 0;
}
```

主线程首先创建一个 `std::unique_lock` 对象 `lock` 并锁定互斥量 `mtx`。然后通过 `owns_lock` 方法检查锁是否成功，如果成功则输出信息。

`owns_lock` 方法提供了一种方便的方法来检查 `std::unique_lock` 对象是否拥有互斥锁，有助于编写更加健壮和可读的代码。

#### 7. 在条件变量中的用法
`std::unique_lock` 的 `wait` 操作主要用于与条件变量一起使用，用于线程同步。条件变量允许一个或多个线程等待某个条件成立，然后继续执行。`std::unique_lock` 提供了一种灵活的锁管理机制，使得在等待条件变量时可以自动释放互斥锁，并在条件满足时重新获得锁。

以下是如何使用 `std::unique_lock` 的 `wait` 操作的示例：

##### 示例代码

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void print_id(int id) {
    std::unique_lock<std::mutex> lock(mtx);
    // Wait until 'ready' becomes true
    cv.wait(lock, [] { return ready; });

    // After the condition is satisfied, the lock is reacquired
    std::cout << "Thread " << id << " is running\n";
}

void set_ready() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
        std::lock_guard<std::mutex> lock(mtx);
        ready = true;
    }
    cv.notify_all(); // Notify all waiting threads
}

int main() {
    std::thread threads[10];
    for (int i = 0; i < 10; ++i) {
        threads[i] = std::thread(print_id, i);
    }

    set_ready();

    for (auto& th : threads) {
        th.join();
    }

    return 0;
}
```

##### 详细解释

1. **互斥锁和条件变量**：
   - `std::mutex mtx;`：用于保护共享数据的互斥锁。
   - `std::condition_variable cv;`：用于线程间同步的条件变量。

2. **线程函数 `print_id`**：
   - `std::unique_lock<std::mutex> lock(mtx);`：使用 `unique_lock` 锁定互斥锁 `mtx`。
   - `cv.wait(lock, [] { return ready; });`：等待条件变量 `cv`。在等待期间，`unique_lock` 会自动释放锁，并在条件满足后重新获得锁。条件是 `ready` 变为 `true`。
   - `std::cout << "Thread " << id << " is running\n";`：条件满足后，线程继续执行。

3. **设置条件的函数 `set_ready`**：
   - `std::this_thread::sleep_for(std::chrono::seconds(1));`：模拟一些准备工作。
   - `ready = true;`：设置条件变量为 `true`，表明条件已经满足。
   - `cv.notify_all();`：通知所有等待的线程，条件已经满足。

4. **主函数 `main`**：
   - 创建并启动10个线程，每个线程执行 `print_id` 函数。
   - 调用 `set_ready` 函数，设置条件变量并通知所有等待线程。
   - 等待所有线程完成。

##### `wait` 方法的工作机制

- `cv.wait(lock, predicate);`：
  - `lock` 是 `std::unique_lock` 类型，保护共享数据。
  - `predicate` 是一个返回 `bool` 类型的函数或lambda表达式。只有当 `predicate` 返回 `true` 时，等待才会结束。
  - 在 `wait` 期间，`unique_lock` 会自动释放互斥锁，以便其他线程能够获得锁并修改共享数据。
  - 当条件变量被通知且 `predicate` 返回 `true` 时，`unique_lock` 会重新获得锁，线程继续执行。

这种机制确保了线程在等待时不会持有锁，从而提高了程序的并发性能，并确保了条件满足时线程能够安全地继续执行。

### 总结

`std::unique_lock` 是一个强大而灵活的锁管理工具，适用于需要复杂锁定机制的场景。它支持延迟锁定、显式解锁和重新锁定，以及尝试锁定等操作，使得在多线程编程中可以更灵活地管理锁。
