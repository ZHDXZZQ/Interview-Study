/*
    策略模式Strategy：定义了算法家族，分别封装起来
    让其之间可以相互替换，使得算法的变化不会影响使用算法的客户    
*/

#include <iostream>
#include <unordered_map>

class Weapon {       //武器基类，即策略基类，算法家族名
public:
    virtual double attack(int power) = 0;
};

class Knife : public Weapon {   //武器刀，攻击力2.2倍
public:
    double attack(int power) override {
        return 2.2 * power;
    }
};

class Axe : public Weapon {     //武器斧，攻击力4.3倍
public:
    double attack(int power) override {
        return 4.3 * power;
    }
};

class Gun : public Weapon {     //武器枪，攻击力21.2倍
public:
    double attack(int power) override {
        return 21.2 * power;
    }
};

class Hand : public Weapon {    //空手，无加成
public:
    double attack(int power) override {
        return power;
    }
};

class WeaponFactory {       //武器工厂，兼具上下文类
public:
    WeaponFactory() {  //初始化武器类，并设置武器
        // 初始化各武器
        armory["gun"] = new Gun();
        armory["axe"] = new Axe();
        armory["knife"] = new Knife();
        armory["hand"] = new Hand();
    }

    double calc_hurt(int atk, std::string type) {         //造成伤害
        if (armory.find(type) != armory.end()) {
            return armory[type]->attack(atk);
        }
        return armory["hand"]->attack(atk);
    }

private:
    std::unordered_map<std::string, Weapon*> armory;    //武器类映射，可以放到工厂内部不对外暴露，这块根据具体情况设置
};

auto weapon_factory = new WeaponFactory();      // 全局声明唯一的武器工厂，这里建议使用饿汉单例模式

class Hero {
public:
    Hero(int atk, std::string weapon = "hand") : atk(atk), weapon(weapon) {} //初始化英雄攻击力和武器

    void set_weapon(std::string type) { //设置英雄的武器
        this->weapon = type;
    }

    double hero_attack() {      //开始攻击
        return weapon_factory->calc_hurt(this->atk, weapon);
    }
private:
    int atk;            //英雄攻击力
    std::string weapon; //英雄武器
};

int main() {
    auto spider_man = new Hero(12); //设置蜘蛛侠
    std::cout << spider_man->hero_attack() << std::endl;
    spider_man->set_weapon("axe");  //使用斧子
    std::cout << spider_man->hero_attack() << std::endl;

    auto iron_man = new Hero(43, "gun");    //设置钢铁侠，初始用枪
    std::cout << iron_man->hero_attack() << std::endl;
    iron_man->set_weapon("knife");          //用刀
    std::cout << iron_man->hero_attack() << std::endl;
    iron_man->set_weapon("");               //置为空，默认用手
    std::cout << iron_man->hero_attack() << std::endl;

    return 0;
}