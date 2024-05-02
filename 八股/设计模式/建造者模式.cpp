/*
    建造者模式：生成器模式。将一个复杂对象的构建与表示分离
    使得同样的构建过程可以创建不同的表示，用户不需要具体的建造过程和细节
    这样避免了用户在建造对象的时候漏掉一些细节。
*/

#include <iostream>
#include <string>
#include <vector>

// 产品类
class Computer {
public:
    void add(std::string part) {    // 建造产品的具体组成
        parts.push_back(part);
    }
    std::string show() {    // 展示最终产品
        std::string computer = "当前电脑的配置为: ";
        for (auto& part : parts) {
            computer += part + "  ";
        }
        return computer;
    }
private:
    std::vector<std::string> parts; // 产品的具体组成部分
};

// 建造者基类，定义产品每个部分的建造函数，保证基础部分一定被建造
class ComputerBuilder {
public:
    virtual void build_cpu() = 0;
    virtual void build_mem() = 0;
    virtual void build_io() = 0;
    virtual Computer* get_product() = 0;
};

// 具体的建造者
class LenovoBuilder : public ComputerBuilder {
public:
    LenovoBuilder() {
        computer = new Computer();
    }
    void build_cpu() override {
        computer->add("联想自研cpu");
    }
    void build_mem() override {
        computer->add("联想自研memory系统");
    }
    void build_io() override {
        computer->add("联想自研IO系统");
    }
    Computer* get_product() override {
        return computer;
    }
private:
    Computer* computer;
};

// 具体的建造者
class AppleBuilder : public ComputerBuilder {
public:
    AppleBuilder() {
        computer = new Computer();
    }
    void build_cpu() override {
        computer->add("苹果M3处理器");
    }
    void build_mem() override {
        computer->add("苹果自研memory系统");
    }
    void build_io() override {
        computer->add("苹果自研IO系统");
    }
    Computer* get_product() override {
        return computer;
    }
private:
    Computer* computer;
};

// 建造执行者，调用该接口完成建造
class Builder {
public:
    void build_computer(ComputerBuilder* builder) {
        builder->build_cpu();
        builder->build_mem();
        builder->build_io();
    }
};

int main() {
    Builder* builder = new Builder();       // 建造执行者
    LenovoBuilder* lb = new LenovoBuilder();    // 具体的建造者，至少保证了基础部件全部建造
    AppleBuilder* ab = new AppleBuilder();

    builder->build_computer(lb);
    builder->build_computer(ab);

    Computer* lenovo = lb->get_product();   //获取建造完成的产品
    Computer* apple = ab->get_product();
    std::cout << lenovo->show() << std::endl;
    std::cout << apple->show() << std::endl;
    lenovo->add("NVIDIA GeForce RTX 4090 显卡");    // 支持自主扩展建造
    std::cout << lenovo->show() << std::endl;
    return 0;
}