// 使用信号量来实现不停的创建两个线程来交替打印，应用PV操作
// 本质上，信号量既可以实现同步，也可以实现互斥，是万能的。
// 互斥锁mutex其实就是信号量取值在0，1的实例
// 条件变量就是带有唤醒功能的，且没值的信号量，必须搭配互斥锁使用
// 编译命令 g++ -pthread 使用两个线程交替打印1-100\(信号量实现\).cpp -o test

#include <iostream>
#include <thread>
#include <semaphore.h>      //<semaphore>只适用于C++20之后
// semaphore实现了acquire和release，即PV操作，如果初值为1，则可当作互斥锁

sem_t sem1;
sem_t sem2;
int num = 0;

void print_odd(int i) {
    while (num < 99) {
        sem_wait(&sem1);
        ++ num;
        std::cout << "thread" << i << " : " << num << std::endl;
        sem_post(&sem2);
    }
    pthread_exit(NULL);  // 线程主动退出函数，等价于 return;
}

void print_even(int i) {
    while (num < 100) {
        sem_wait(&sem2);
        ++ num;
        std::cout << "thread" << i << " : " << num << std::endl;
        sem_post(&sem1);
    }
    return;
}

int main() {
    sem_init(&sem1, 0, 1);
    sem_init(&sem2, 0, 0);
    //int sem_init(sem_t *sem, int pshared, unsigned int value);
    // 第二个参数表示进程还是线程，一般填0表示线程；第三个参数表示的是信号量的初始值
    std::thread thread_1(print_odd, 1);
    std::thread thread_2(print_even, 2);
    thread_1.detach();
    thread_2.join();
    sem_destroy(&sem1);      //销毁信号量
    sem_destroy(&sem2);
    return 0;
}