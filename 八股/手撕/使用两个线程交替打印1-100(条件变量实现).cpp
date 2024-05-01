// 使用条件变量实现，使用两个线程交替打印1-100
// 需要和互斥锁搭配使用
// 编译命令 g++ -pthread 使用两个线程交替打印1-100\(条件变量实现\).cpp -o test

#include <thread>
#include <condition_variable>
#include <mutex>
#include <iostream>
#include <unistd.h>

std::condition_variable cv;
std::mutex locker;
int num = 0;

void print_odd(int i) {
    while (num < 100) {
        std::unique_lock<std::mutex> lock(locker);  //可以手动lock和unlock，此时自动锁定，会自动释放
        if (num % 2 == 1) {
            cv.wait(lock);
        }
        ++ num;
        // sleep(1);   //睡眠1秒
        if (num >= 100) {
            pthread_exit(nullptr);
        }
        std::cout << "thread" << i << " : " << num << std::endl;
        cv.notify_all();
        // lock.unlock();       //unique_lock自动实现释放锁
    }
}

void print_even(int i) {
    while (num < 100) {
        std::unique_lock<std::mutex> lock(locker);  //可以手动lock和unlock，此时自动锁定，会自动释放，需要使用同一个互斥锁
        if (num % 2 == 0) {
            cv.wait(lock);
        }
        ++ num;
        std::cout << "thread" << i << " : " << num << std::endl;
        cv.notify_all();
    }
}

int main() {
    std::thread thread_1(print_odd, 1);
    std::thread thread_2(print_even, 2);
    thread_1.join();
    thread_2.join();
    return 0;
}