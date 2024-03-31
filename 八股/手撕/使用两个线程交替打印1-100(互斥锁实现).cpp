// 两个线程交替打印1-100，互斥锁实现

#include <iostream>
#include <thread>
#include <mutex>

std::mutex locker;      //互斥锁
int num = 0;

void print_odd(int id) {    //传入参数可以自主设定
    while (num < 100) {
        locker.lock();
        if (num < 100 && num % 2 == 0) {    //需要加一层num<100的判断，不然会打印出101
            std::cout << "Thread " << id << ": " << ++ num << std::endl;
        }
        locker.unlock();
    }
}

void print_even(int id) {
    while (num < 100) {
        locker.lock();
        if (num < 100 && num % 2 == 1) {
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
    std::cout << "Main thread ID: " << std::this_thread::get_id() << std::endl; //获取线程id
    std::cout << "Main thread ID: " << pthread_self() << std::endl;            //使用UNIX系统的方式获取线程id
    std::cout << "两个线程已经打印完成!" << std::endl;
    return 0;
}
