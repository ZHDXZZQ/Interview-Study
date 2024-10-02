/* 
    之前的工厂方法模式是定义一个用于创建对象的接口，让子类决定实例化哪一个类
    抽象工厂模式Abstract Factory，提供一个创建一系列相关或相互依赖对象的接口，而无需指定它们具体的类。
    好处：利于交换产品系列，让具体的创建实例过程与客户端分离。
    所有在用简单工厂的地方，都可以考虑用反射技术取出switch或if
    抽象工厂模式提供了一种创建产品族的方式，避免了对具体类的依赖，提高了系统的灵活性和可扩展性。
    它适用于需要同时创建多种类型对象的场景，尤其是在对象之间有相互依赖关系时。
*/
#include <iostream>
#include <memory>

// 抽象产品 A
class AbstractProductA {
public:
    virtual void use() = 0; // 抽象方法
};

// 抽象产品 B
class AbstractProductB {
public:
    virtual void use() = 0; // 抽象方法
};

// 具体产品 A1
class ProductA1 : public AbstractProductA {
public:
    void use() override {
        std::cout << "Using Product A1" << std::endl;
    }
};

// 具体产品 A2
class ProductA2 : public AbstractProductA {
public:
    void use() override {
        std::cout << "Using Product A2" << std::endl;
    }
};

// 具体产品 B1
class ProductB1 : public AbstractProductB {
public:
    void use() override {
        std::cout << "Using Product B1" << std::endl;
    }
};

// 具体产品 B2
class ProductB2 : public AbstractProductB {
public:
    void use() override {
        std::cout << "Using Product B2" << std::endl;
    }
};

// 抽象工厂
class AbstractFactory {
public:
    virtual std::shared_ptr<AbstractProductA> createProductA() = 0; // 创建产品 A
    virtual std::shared_ptr<AbstractProductB> createProductB() = 0; // 创建产品 B
};

// 具体工厂 1
class ConcreteFactory1 : public AbstractFactory {
public:
    std::shared_ptr<AbstractProductA> createProductA() override {
        return std::make_shared<ProductA1>();
    }

    std::shared_ptr<AbstractProductB> createProductB() override {
        return std::make_shared<ProductB1>();
    }
};

// 具体工厂 2
class ConcreteFactory2 : public AbstractFactory {
public:
    std::shared_ptr<AbstractProductA> createProductA() override {
        return std::make_shared<ProductA2>();
    }

    std::shared_ptr<AbstractProductB> createProductB() override {
        return std::make_shared<ProductB2>();
    }
};

// 客户端代码
int main() {
    std::shared_ptr<AbstractFactory> factory1 = std::make_shared<ConcreteFactory1>();
    std::shared_ptr<AbstractProductA> productA1 = factory1->createProductA();
    std::shared_ptr<AbstractProductB> productB1 = factory1->createProductB();
    
    productA1->use(); // 输出: Using Product A1
    productB1->use(); // 输出: Using Product B1

    std::shared_ptr<AbstractFactory> factory2 = std::make_shared<ConcreteFactory2>();
    std::shared_ptr<AbstractProductA> productA2 = factory2->createProductA();
    std::shared_ptr<AbstractProductB> productB2 = factory2->createProductB();
    
    productA2->use(); // 输出: Using Product A2
    productB2->use(); // 输出: Using Product B2

    return 0;
}
