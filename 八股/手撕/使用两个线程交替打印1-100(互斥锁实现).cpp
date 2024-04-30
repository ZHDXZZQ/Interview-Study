// 两个线程交替打印1-100，互斥锁实现
// 线程常用方法：初始化、睡眠、获取线程id、互斥锁、条件变量、信号量、线程分离等
// 锁的使用还可以使用lock_guard和unique_lock

#include <iostream>
#include <thread>
#include <mutex>

std::mutex locker;      //互斥锁
int num = 0;

void print_odd(int id) {    //传入参数可以自主设定
    while (num < 100) {
        locker.lock();
        //try_lock()方法可以用于判断当前锁是否可用，如果可用会返回true并获取锁，否则返回false且不会获取锁
        if (num < 100 && num % 2 == 0) {    //需要加一层num<100的判断，不然会打印出101
            std::cout << "Thread " << id << ": " << ++ num << std::endl;
        }
        locker.unlock();
    }
}

void print_even(int id) {
    while (num < 100) {
        locker.lock();
        if (num < 100 && num % 2 == 1) {    //如果不加判断可能会乱序输出
            std::cout << "Thread " << id << ": " << ++ num << std::endl;
        }
        locker.unlock();
    }
}

int main() {
    std::thread t1(print_odd, 1);   //传递函数指针
    std::thread t2(print_even, 2);
    t1.join();  //join：主线程会等待该子线程结束后才会继续往下执行
    //可以搭配joinable()使用，该函数返回bool类型指的是是否可以被join
    t2.join();  //detach：主线程会继续执行后面的逻辑，而不管该子线程执行情况
    //主线程如果执行完毕，子线程会直接停止执行
    // while (num < 100);   //使用detach的话需要加这句话，不然子线程会被提前退出
    // std::cout << "Main thread ID: " << std::this_thread::get_id() << std::endl; //获取线程id
    // std::cout << "Main thread ID: " << pthread_self() << std::endl;             //使用UNIX系统的方式获取线程id
    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));               //让线程睡眠1000毫秒（1秒）
    // milliseconds替换成second的话指的是秒，如果填0的话会一直睡眠，直到被唤醒
    std::cout << "两个线程已经打印完成!" << std::endl;
    return 0;
}
