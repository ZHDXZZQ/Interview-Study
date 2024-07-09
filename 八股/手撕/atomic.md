`std::atomic` 是 C++11 引入的用于实现原子操作的模板类，提供了一种无锁的线程安全方式来操作共享数据。
它可以避免数据竞争，**保证操作的原子性**，是实现高效并发程序的重要工具。

**用法**
std::atomic 可以用于基本数据类型，比如 int、bool、float 等，也可以用于指针类型

**方法：**
声明和初始化
```C++
#include <atomic>
#include <iostream>

std::atomic<int> atomic_counter(0);

int main() {
    // 初始化时可以指定初始值
    std::atomic<int> atomic_counter2(5);

    std::cout << "Initial value: " << atomic_counter.load() << std::endl;
    return 0;
}

```
1. load() 和store()
```C++
#include <atomic>
#include <iostream>
#include <thread>

std::atomic<bool> ready(false);

void wait_for_ready() {
    while (!ready.load()) {
        std::this_thread::yield();
    }
    std::cout << "Ready!" << std::endl;
}

void set_ready() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    ready.store(true);
    std::cout << "Set to ready." << std::endl;
}

int main() {
    std::thread t1(wait_for_ready);
    std::thread t2(set_ready);

    t1.join();
    t2.join();

    return 0;
}

```

2. compare_exchange_strong() 和 compare_exchange_weak() 即CAS操作
- compare_exchange_strong 和 compare_exchange_weak 都是 std::atomic 提供的原子操作，用于实现无锁的数据结构和算法。
这两个函数用于比较原子的当前值与期望值，如果相等，则将原子的值替换为新值。这两个函数的主要区别在于它们处理竞争条件的方式。

compare_exchange_strong
compare_exchange_strong 是一个强力的比较和交换操作。它会不断重试直到成功，因此它更适合在需要严格保证操作成功的场景中使用。

compare_exchange_weak
compare_exchange_weak 是一个弱比较和交换操作。它在某些情况下可能会失败，即使没有数据竞争。
这种操作设计用于在实现循环和自旋锁等算法时，可以通过快速失败来优化性能。
相比之下，它在竞争情况下失败的概率更高，但在这种情况下重试更便宜。

compare_exchange_strong：适用于需要保证操作成功的场景，例如实现无锁数据结构时。
compare_exchange_weak：适用于自旋锁和其他高竞争场景，利用快速失败进行优化。

```C++
#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

std::atomic<int> atomicCounter(0);
// bool compare_exchange_strong(T& expected, T desired,
//                              std::memory_order order = std::memory_order_seq_cst) noexcept;
// expected: 一个引用，用于传入期望的值。如果当前值不等于 expected，则 compare_exchange_strong 会将当前值写入 expected。
// desired: 希望设置的新值。
// order: 内存顺序，默认为 std::memory_order_seq_cst，可以选择其他内存顺序来优化性能。
// 返回值
// 如果当前值等于 expected，返回 true，并且将当前值更新为 desired。
// 如果当前值不等于 expected，返回 false，并且将当前值写入 expected， 不会更新当前值为desired。

void strong_increment() {
    int expected;
    for (int i = 0; i < 1000; ++i) {
        expected = atomicCounter.load();
        while (!atomicCounter.compare_exchange_strong(expected, expected + 1)) {
            // 如果compare_exchange_strong失败，expected会被更新为atomicCounter的当前值
        }
    }
}

void weak_increment() {
    int expected;
    for (int i = 0; i < 1000; ++i) {
        expected = atomicCounter.load();
        while (!atomicCounter.compare_exchange_weak(expected, expected + 1)) {
            // 如果compare_exchange_weak失败，expected会被更新为atomicCounter的当前值
        }
    }
}

int main() {
    std::vector<std::thread> threads;

    // 使用compare_exchange_strong进行递增操作
    for (int i = 0; i < 5; ++i) {
        threads.push_back(std::thread(strong_increment));
    }

    // 使用compare_exchange_weak进行递增操作
    for (int i = 0; i < 5; ++i) {
        threads.push_back(std::thread(weak_increment));
    }

    // 等待所有线程完成
    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Final value of atomicCounter: " << atomicCounter << std::endl;

    return 0;
}

```

3. fetch_add() 和 fetch_sub()，自增和自减，可前置可后置
```C++
#include <atomic>
#include <iostream>

int main() {
    std::atomic<int> atomic_int(0);
    atomic_int++;
    atomic_int--;
    atomic_int.fetch_add(5);
    atomic_int.fetch_sub(2);
    std::cout << "Current value: " << atomic_int.load() << std::endl;
    return 0;
}

```

4. exchange(int new_num)：替换为新值，返回旧值
```C++
#include <atomic>
#include <iostream>

int main() {
    std::atomic<int> atomic_int(5);
    int old_value = atomic_int.exchange(10);
    std::cout << "Old value: " << old_value << ", New value: " << atomic_int.load() << std::endl;
    return 0;
}

```

5. 指针操作
```C++
#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

std::atomic<int*> atomic_ptr;

void set_value(int* p) {
    atomic_ptr.store(p);
}

void print_value() {
    while (atomic_ptr.load() == nullptr) {
        std::this_thread::yield();
    }
    std::cout << "Value: " << *atomic_ptr.load() << std::endl;
}

int main() {
    int x = 42;
    std::thread t1(print_value);
    std::thread t2(set_value, &x);

    t1.join();
    t2.join();

    return 0;
}
```

**内存顺序规则：**
1. memory_order_relaxed：最弱的顺序保证，只保证操作是原子的，不保证操作的顺序。
2. memory_order_consume：本线程后续所有依赖于本原子类型的操作必须在本操作后完成。
3. memory_order_acquire：保证本线程中后续的所有读操作在此操作之后完成。
4. memory_order_release：保证本线程中在此操作之前的所有写操作完成。
5. memory_order_acq_rel：结合 acquire 和 release 的语义。
6. memory_order_seq_cst：最强的顺序保证，所有线程中的操作都按严格的顺序执行。 默认级别

```C++
#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

std::atomic<int> atomic_int(0);

void thread_func() {
    atomic_int.fetch_add(1, std::memory_order_relaxed);
}

int main() {
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(thread_func);
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Final value: " << atomic_int.load(std::memory_order_relaxed) << std::endl;    // 不做任何保障
    return 0;
}

```