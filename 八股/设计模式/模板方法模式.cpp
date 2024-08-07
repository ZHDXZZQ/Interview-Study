/*
    模板方法模式TemplateMethod：定义一个操作中的算法的骨架，而将一些步骤延迟到子类中。
    使得子类可以不改变一个算法的结构即可重定义该算法的某些特定步骤
    提供了一个很好的代码复用
*/

// 示例：制作饮料
// 假设我们要创建一个制作饮料的模板方法，饮料可以是茶（Tea）或者咖啡（Coffee）。
// 制作饮料的步骤包括：烧水、冲泡、倒入杯中和添加配料。
// 茶和咖啡在冲泡和添加配料的步骤上有所不同。

#include <iostream>

// 抽象模板类，有一个具体的方法给用户调用，包含了顶级逻辑骨架，而具体的操作在抽象的操作中，推迟到子类实现
class Beverage {
private:
    void boilWater() {
        std::cout << " 烧水 " << std::endl;
    }

    void pourInCup() {
        std::cout << " 倒入杯中 " << std::endl;
    }

    virtual void brew() = 0;
    virtual void addCondiments() = 0;

public:
    Beverage() = default;
    virtual ~Beverage() = default;

    void prepareRecipe() {
        boilWater();
        brew();
        pourInCup();
        addCondiments();
    }
};

// 实现父类定义的抽象方法
class Tea : public Beverage {
public:
    void brew() override {
        std::cout << " 沏茶 " << std::endl;
    }

    void addCondiments() override {
        std::cout << " 添加配料柠檬 " << std::endl;
    }
};

class Coffee : public Beverage {
public:
    Coffee() {}
    void brew() override {
        std::cout << " 冲咖啡 " << std::endl;
    }

    void addCondiments() override {
        std::cout << " 添加配料糖和牛奶 " << std::endl;
    }
};

int main() {
    Tea* tea = new Tea();
    Beverage* coffee = new Coffee();

    std::cout << "Making tea:" << std::endl;
    tea->prepareRecipe();

    std::cout << "\nMaking coffee:" << std::endl;
    coffee->prepareRecipe();

    delete tea;
    delete coffee;

    return 0;
}
