在 C++ 中，`std::promise` 和 `std::future` 是用于线程间通信的同步机制。`std::promise` 提供了一种设置值或异常的方式，另一个线程可以通过 `std::future` 获取这些值或捕获异常。它们常用于跨线程传递数据、任务结果或处理异步操作。

### 基本概念
- **`std::promise`**：用于在一个线程中设置一个值或抛出异常。
- **`std::future`**：用于在另一个线程中获取由 `std::promise` 设置的值或捕获异常。

`std::promise` 和 `std::future` 通常配合使用，`promise` 负责“承诺”（设置值），`future` 负责“获取”（接收值）。

### `std::promise` 和 `std::future` 的基本用法

#### 1. 简单示例：通过 `std::promise` 在一个线程中设置值，另一个线程通过 `std::future` 获取该值。

```cpp
#include <iostream>
#include <thread>
#include <future>

void set_value(std::promise<int>& prom) {
    std::this_thread::sleep_for(std::chrono::seconds(2));  // 模拟耗时操作
    prom.set_value(10);  // 设置值
}

int main() {
    std::promise<int> prom;  // 创建一个 promise 对象
    std::future<int> fut = prom.get_future();  // 获取与 promise 相关联的 future 对象

    // 创建一个线程，在其中设置 promise 的值
    std::thread t(set_value, std::ref(prom));

    // 主线程等待并获取 future 的值
    std::cout << "Waiting for value..." << std::endl;
    std::cout << "Value received: " << fut.get() << std::endl;

    t.join();  // 等待子线程结束
    return 0;
}
```
在这个例子中，子线程通过 `prom.set_value(10)` 设置值，主线程通过 `fut.get()` 获取到这个值。

### 常用的成员函数

#### `std::promise` 成员函数：
- **`set_value(T value)`**：设置 promise 的值。`future.get()` 调用时会返回这个值。
- **`set_exception(std::exception_ptr)`**：设置一个异常，该异常会在 `future.get()` 中抛出。
- **`get_future()`**：获取与 promise 关联的 `std::future` 对象。

#### `std::future` 成员函数：
- **`get()`**：等待异步操作完成并返回结果，若 promise 设置了异常则会抛出异常。
- **`wait()`**：阻塞当前线程，直到有结果返回。
- **`valid()`**：检查 `future` 是否有效，通常用于判断 `get()` 是否可以成功调用。

### 2. 使用 `std::promise` 设置异常
`std::promise` 可以设置异常，另一个线程可以通过 `std::future` 来捕获并处理该异常。

```cpp
#include <iostream>
#include <thread>
#include <future>
#include <stdexcept>

void set_exception(std::promise<int>& prom) {
    std::this_thread::sleep_for(std::chrono::seconds(2));  // 模拟耗时操作
    try {
        throw std::runtime_error("Error occurred in the task!");  // 抛出异常
    } catch (...) {
        prom.set_exception(std::current_exception());  // 将异常传递给 promise
    }
}

int main() {
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();

    // 创建一个线程，设置异常
    std::thread t(set_exception, std::ref(prom));

    // 主线程等待并获取 future 的结果
    try {
        std::cout << "Waiting for result..." << std::endl;
        int result = fut.get();  // 获取值或捕获异常
        std::cout << "Result received: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    t.join();
    return 0;
}
```
在这个例子中，子线程通过 `prom.set_exception()` 设置了一个异常，主线程在调用 `fut.get()` 时捕获并处理该异常。

### 场景应用

1. **线程间通信**：
   在多线程编程中，一个线程可以通过 `std::promise` 向另一个线程传递计算结果。`std::promise` 与 `std::future` 的组合使得线程可以同步和安全地交换数据，而无需使用显式的条件变量和锁。

2. **任务结果传递**：
   当你有一个耗时任务，并希望在任务完成时将结果传递给主线程，`std::promise` 是非常合适的。它避免了轮询的复杂性，并简化了等待任务完成的操作。

3. **异步操作错误处理**：
   `std::promise` 提供了方便的机制来将异常从一个线程传递到另一个线程。例如，当一个后台任务发生错误时，可以通过 `set_exception` 将异常传递到主线程，让主线程处理该错误。

4. **异步框架的基础**：
   `std::promise` 和 `std::future` 作为 C++ 标准库的一部分，可以作为构建异步框架的基础工具。在复杂的并发应用中，它们可以与其他工具（如 `std::async`、`std::packaged_task`）一起使用来管理任务。

### 3. 多线程协同工作
多个线程可以通过 `std::promise` 和 `std::future` 来协同工作，保证数据同步。例如，可以使用它们来协调生产者-消费者模式：

```cpp
#include <iostream>
#include <thread>
#include <future>

void producer(std::promise<int>& prom) {
    int value = 42;
    std::this_thread::sleep_for(std::chrono::seconds(1));  // 模拟生产过程
    std::cout << "Produced value: " << value << std::endl;
    prom.set_value(value);  // 生产者将值放入 promise 中
}

void consumer(std::future<int>& fut) {
    std::cout << "Waiting for value..." << std::endl;
    int value = fut.get();  // 消费者等待并获取值
    std::cout << "Consumed value: " << value << std::endl;
}

int main() {
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();

    std::thread prod_thread(producer, std::ref(prom));
    std::thread cons_thread(consumer, std::ref(fut));

    prod_thread.join();
    cons_thread.join();

    return 0;
}
```
在这个生产者-消费者示例中，生产者线程通过 `promise.set_value()` 设置了一个值，消费者线程通过 `future.get()` 获取并消费了该值。

### 总结
- **`std::promise`** 是 C++ 提供的异步编程机制，用于在线程之间传递值或异常。
- 与 **`std::future`** 搭配使用，主线程可以异步等待子线程的执行结果并安全地处理。
- `std::promise` 适用于多线程通信、任务结果传递、异步错误处理等场景，简化了线程间数据同步的复杂性。