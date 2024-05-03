/*
    工厂方法模式：定义一个用于创建对象的接口，让子类决定实例化哪一个类。
    使得一个类的实例化延迟到其子类。
    与简单工厂模式相比，简单工厂模式在到来一个新的子类时，需要修改工厂类，违背了开放-封闭原则。
    工厂方法模式把简单工厂的内部逻辑判断移动到了客户端代码实现。
    简单工厂模式：基类创建多个子类，工厂判断选择哪个子类创建。
    工厂方法模式：基类创建多个子类，每个子类对应一个工厂子类，客户端创建对应的工厂子类来实例化子类。
    优点在于，创建对应子类时使用的是同一个接口，只需要修改工厂子类就可以实现同接口创建不同子类。
*/

#include <iostream>
#include <string>
#include <unordered_map>

// 对象基类
class FastFood {
public:
    virtual void make_hamburger() {
        std::cout << "制作原始汉堡" << std::endl;
    }
    virtual void make_fries() {
        std::cout << "制作原始薯条" << std::endl;
    }
    virtual void make_chicken() {
        std::cout << "制作原始炸鸡" << std::endl;
    }
};

// 对象子类
class KFC : public FastFood {
    virtual void make_hamburger() override {
        std::cout << "制作肯德基汉堡" << std::endl;
    }
    virtual void make_fries() override {
        std::cout << "制作肯德基薯条" << std::endl;
    }
    virtual void make_chicken() override {
        std::cout << "制作肯德基炸鸡" << std::endl;
    }
};

// 对象子类
class McDonald : public FastFood {
    void make_hamburger() override {
        std::cout << "制作麦当劳汉堡" << std::endl;
    }
    void make_fries() override {
        std::cout << "制作麦当劳薯条" << std::endl;
    }
};

// 对象子类
class Wallace : public FastFood {};



// 简单工厂模式，每新增一个类需要修改工厂类
class SimpleFactory {
public:
    SimpleFactory() {
        FastFoodType["肯德基"] = 1;
        FastFoodType["麦当劳"] = 2;
        FastFoodType["华莱士"] = 3;
    }
    FastFood* create_fast_food(std::string type) {  // 可以定义为静态
        auto choice = FastFoodType[type];
        switch (choice) {
            case 0: {       //大括号可以不加
                std::cout << "无对应对象" << std::endl;
                return new FastFood();
            }
            case 1: {
                return new KFC();
            }
            case 2: {
                return new McDonald();
            }
            case 3: {
                return new Wallace();
            }
            default: {
                std::cout << "无对应对象" << std::endl;
                return new FastFood();
            }
        }
        std::cout << "无对应对象" << std::endl;
        return new FastFood();
    }
private:
    std::unordered_map<std::string, int> FastFoodType;  // 字符串映射
};

// 工厂方法模式基类
class Factory {
public:
    virtual FastFood* make_fast_food () = 0;
};

// 工厂子类
class KFCFactory : public Factory {
public:
    FastFood* make_fast_food() override {
        return new KFC();
    }
};

// 工厂子类
class McDonaldFactory : public Factory {
public:
    FastFood* make_fast_food() override {
        return new McDonald();
    }
};

// 工厂子类
class WallaceFactory : public Factory {
public:
    FastFood* make_fast_food() override {
        return new Wallace();
    }
};

int main() {
    // 简单工厂模式应用
    SimpleFactory* sf = new SimpleFactory();
    auto ff = sf->create_fast_food("德基"); // 测试错误的名称
    ff->make_chicken();

    std::cout << "-------------------------" << std::endl;

    // 工厂方法模式应用
    Factory* factory = new McDonaldFactory();       // 实例化不同的子类只需要修改这里的工厂子类
    FastFood* fast_food = factory->make_fast_food();

    fast_food->make_chicken();
    fast_food->make_fries();
    fast_food->make_hamburger();

    std::cout << "-------------------------" << std::endl;

    factory = new WallaceFactory();
    fast_food = factory->make_fast_food();
    fast_food->make_chicken();
    fast_food->make_fries();
    fast_food->make_hamburger();

    return 0;
}