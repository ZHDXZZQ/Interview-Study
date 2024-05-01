/* 
 适配器模式Adaptor： 将一个类的接口转换成客户希望的另外一个接口，
 使得原本由于接口不能兼容而不能一起工作的类可以一起工作。
 即，客户使用自己的接口可以操控原本无法操控的东西，
 方法就是将客户自己的接口，适配成原本可用的接口。
*/
#include <iostream>

class Usb;

// 用电器，只能使用usb进行充电
class PowerBank {
friend Usb; //仅usb可以访问private
public:
    PowerBank(int power = 0) : power(power) {}
    int get_power() {   //获取当前电量
        return power;
    }
private:
    int power;
};

// 需要适配的类，即将目标类适配成该类，所有新来的类都要变成该类的方法来调用
class Usb {
public:
    Usb(int input) : v(input) {}
    // 假设充电仅支持使用usb充电
    void charge(PowerBank* pb) {
        pb->power += v;
        std::cout << "use usb charge : " << v << " success ! " << std::endl;
    };

private:
    int v;
};

// 目标类，客户使用的类，需要转换成统一的类，即调用Usb类的方法
class TypeC {
public:
    TypeC(int input) : v(input) {}

    virtual void charge(PowerBank* pb) {
        // pb->power += v;  无法充电
        std::cout << "use type_c charge : " << v << " failed !" << std::endl;
    }

private:
    int v;
};

// 适配器类，将TypeC类转化成Usb类，调用typec的充电可以使用usb充
class Adapter : public TypeC {
public:
    Adapter(int input) : TypeC(input) {
        usb = new Usb(input);
    }

    void charge(PowerBank* pb) override {
        std::cout << " 使用 type c 充电， 转换成usb充电 !" << std::endl;
        usb->charge(pb);
    }
private:
    Usb* usb;
};

int main() {
    PowerBank* pb = new PowerBank(5);
    std::cout << "当前电量： " << pb->get_power() << std::endl;

    TypeC* target = new Adapter(220);
    target->charge(pb);   //使用type c充电，但是实际转换成了usb进行充电
    std::cout << "当前电量： " << pb->get_power() << std::endl;

    target->TypeC::charge(pb);
    std::cout << "当前电量： " << pb->get_power() << std::endl;

    auto typec = new TypeC(50);
    typec->charge(pb);
    std::cout << "当前电量： " << pb->get_power() << std::endl;

    auto usb = new Usb(44);
    usb->charge(pb);
    std::cout << "当前电量： " << pb->get_power() << std::endl;

    return 0;
}