/*
    装饰器模式：Decorator
    动态地给一个对象添加额外的职责，就增加功能来说，比生成子类更为灵活
    把每个要装饰的功能放在单独的类中，让这个类包装它所要装饰的对象
    有效地把类的核心职责和装饰功能区分开了，可以去除相关类中重复的装饰逻辑
*/

#include <iostream>
#include <string>

// 基类，被装饰的类
class Hero {
public:
    Hero() {}
    Hero(std::string name) : name(name) {}
    virtual std::string get_equipment() {
        return "英雄: " + name + " 的装备有: 手, ";
    }
private:
    std::string name;
};

// 装饰器，对被装饰的类进行装饰
class Decorator : public Hero {
public:
    Decorator(Hero* hero) : hero(hero) {}
    std::string get_equipment() override {
        if (hero != nullptr) {
            return hero->get_equipment();
        }
        return "未找到对应英雄";
    }
protected:
    Hero* hero;
};

// 功能类，装饰基类
class Knife : public Decorator {
public:
    Knife(Hero* hero) : Decorator(hero) {}
    std::string get_equipment() override {  // 装饰英雄的武器
        std::string cur_equip = Decorator::get_equipment();
        cur_equip += " 刀, ";
        return cur_equip;
    }
};

class Gun : public Decorator {
public:
    Gun(Hero* hero) : Decorator(hero) {}
    std::string get_equipment() override {  // 装饰英雄的武器
        std::string cur_equip = Decorator::get_equipment();
        cur_equip += " 枪, ";
        return cur_equip;
    }
};

int main() {
    Hero* iron_man = new Hero("iron man");
    auto iron_man_with_kinfe = new Knife(iron_man);
    std::cout << iron_man_with_kinfe->get_equipment() << std::endl;

    auto iron_man_all = new Gun(iron_man_with_kinfe);
    std::cout << iron_man_all->get_equipment() << std::endl;;

    return 0;
}