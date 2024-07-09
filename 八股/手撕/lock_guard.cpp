/*
    std::lock_guard 是 C++ 标准库中的一个模板类，用于在一个作用域中管理一个互斥锁（mutex）。
    它通过 RAII（Resource Acquisition Is Initialization）机制在构造函数中锁定一个互斥锁，并在析构函数中解锁，
    从而确保锁在所有代码路径上都能正确地释放，避免了死锁和其他多线程问题。

    使用场景
    std::lock_guard 主要用于多线程编程中的临界区保护，确保某段代码在某个时间点只有一个线程能访问，从而防止数据竞争和不一致性。
    
    典型场景包括:
    保护共享数据：在多线程环境中对共享数据进行修改时，需要确保只有一个线程能进行修改。
    简化锁管理：通过 RAII 机制简化锁的管理，避免手动解锁带来的麻烦和错误。
    异常安全：即使在异常发生的情况下，也能确保互斥锁会被正确释放

    简单理解！就是mutex的自动释放版本，上锁的方法加了一层类保护
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <unistd.h>

std::mutex mtx; // 定义一个全局的互斥锁
int shared_data = 0; // 共享数据

void increment(int id) {
    for (int i = 0; i < 5; ++i) {
        std::lock_guard<std::mutex> lock(mtx); // 自动锁定互斥锁
        // sleep(1);
        ++shared_data; // 访问和修改共享数据
        std::cout << "Thread " << id << " incremented shared_data to " << shared_data << std::endl;
        // 互斥锁在此作用域结束时自动解锁，即析构时自动unlock
        // lock.~lock_guard();
        // sleep(1);
    }
}

int main() {
    std::vector<std::thread> threads;
    for (int i = 0; i < 3; ++i) {
        threads.emplace_back(increment, i); // 创建多个线程
    }

    for (auto& th : threads) {
        th.join(); // 等待所有线程完成
    }

    std::cout << "Final value of shared_data: " << shared_data << std::endl;
    return 0;
}
