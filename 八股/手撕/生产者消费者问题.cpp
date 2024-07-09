// 生产者消费者问题：一组生产者和一组消费者共享一个初始为空，大小为n的缓冲区，只有缓冲区没满的时候，生产者才能把消息放入缓冲区，否则必须等待；只有缓冲区不空时，消费者才能取出消息，否则必须等待。由于缓冲区是临界资源，它只允许一个生产者放入消息，或者一个消费者从中取出消息
// 本题可以使用条件变量实现，该方法我们放到了使用自制线程池的方法中，这里我们用传统的解法，即互斥锁和判断空满来实现
// 另外一篇的解法，我们打破了原有的缓冲区大小n上限，而是生产者无休止工作，可以通过条件变量唤醒睡眠的消费者线程消费

#include <iostream>
#include <mutex>
#include <semaphore.h>
#include <unistd.h>
#include <thread>

// std::this_thread::yield() 是 C++ 标准库中用于线程管理的一个函数。
// 它的作用是提示操作系统当前线程愿意放弃自己的 CPU 时间片，让操作系统调度其他线程运行。
// 这个函数通常用于多线程编程中的某些场景，以提高程序的响应性和性能。

sem_t product;          //使用信号量模拟产品，当然也可以使用普通的int变量和互斥锁实现
sem_t empty;            //当前缓冲区的空位
std::mutex locker;      //互斥锁，用于访问临界资源
int cur_product = 0;    //记录产品数量


void producer(int i) {
    while (1) {
        sleep(1);       //睡眠1秒模拟生产过程，由于是多线程并行，所以会1秒钟执行8个线程
        sem_wait(&empty);   //pv操作维持同步关系，空位-1
        locker.lock();      //操作临界资源使用互斥关系
        ++ cur_product;
        std::cout << "thread " << i << " is produced a product." << std::endl;
        std::cout << "current product is " << cur_product << std::endl;
        sem_post(&product); //产品数量+1
        locker.unlock();
    }
}

void consumer(int i) {
    while (1) {
        sleep(1);       //模拟购买的过程
        sem_wait(&product); //产品数量-1
        locker.lock();
        -- cur_product;
        std::cout << "thread " << i << " is buy a product." << std::endl;
        std::cout << "current product is " << cur_product << std::endl;
        sem_post(&empty);   //空位+1
        locker.unlock();
    }
}

int main() {
    sem_init(&product, 0, 0);       //初始化产品数量为0
    sem_init(&empty, 0, 8);         //初始化空位为8，即最多生产8个产品
    //模拟4个生产者
    for (int i = 0; i < 4; ++ i) {
        std::thread my_thread(producer, i);
        my_thread.detach();         //这里必须detach，如果使用join()将会一直执行第一个线程
    }
    //模拟3个消费者
    for (int i = 0; i < 4; ++ i) {
        std::thread my_thread(consumer, i);
        my_thread.detach();
    }
    sleep(100);                     //因为前面使用了detach，所以这里睡眠100秒等待线程执行，
    return 0;
}