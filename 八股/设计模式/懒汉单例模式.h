// 线程安全 懒汉模式
#include <mutex>

class single {
private:
    static single *p;
    static std::mutex locker;

    single() {}
    ~single() {}

public:
    static single* get_instance();
};

std::mutex single::locker;      //类中的静态变量需要在类外声明
single* single::p = NULL;

single* single::get_instance() {
    if (p == NULL) {            //一重判断
        locker.lock();
        if (p == NULL) {        //双重判断，防止其他线程进入了一重判断但在等待锁的情况
            p = new single();   //创建一个单例
        }
        locker.unlock();
    }
    return p;
}