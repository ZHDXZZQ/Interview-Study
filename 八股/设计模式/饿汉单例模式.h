//饿汉模式，运行时即初始化

class single {
private:
    static single *p;
    single() {}
    ~single() {}

public:
    static single* get_instance();
};

single* single::p = new single();   //启动时初始化
single* single::get_instance() {
    return p;
}