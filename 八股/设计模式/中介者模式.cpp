/*
    中介者模式Mediator：用一个中介对象来封装一系列交互。
    中介者各对象不需要显示的相互引用，从而松散耦合，而且可以独立改变它们之间的交互
*/

#include <iostream>
#include <windows.h>

class Country;

// 联合国基类，中介者继承使用
class UnitedNations {
friend class USA;   // 声明友元类访问declare，方便访问get_message
friend class CHN;
private:
    virtual void declare(std::string_view message, Country* nation) = 0;
};

// 国家基类，中介者的服务对象
class Country {
public:
    Country(UnitedNations* mediator) : mediator(mediator) {}

private:
    virtual void get_message(std::string_view message) = 0; // 在中介者中访问

protected:
    UnitedNations* mediator;    // 在子类中可以访问

// 在这里声明友元类也不行，为什么？
};

// 美国子类，通过中介者交互
class USA final : public Country {
friend class UnitedNationsSecurityCouncil;
public:
    USA(UnitedNations* mediator) : Country(mediator) {}

    void declare(std::string_view message) {
        mediator->declare(message, this);
    }

private:
    void get_message(std::string_view message) override {
        std::cout << "USA GET MESSAGE: " << message << std::endl;
    }
};

// 中国子类，通过中介者交互
class CHN final : public Country {
friend class UnitedNationsSecurityCouncil;  // 这里为什么只能用友元类而不能用友元函数？为什么这里会报错不可访问安理会类的private
public:
    CHN(UnitedNations* mediator) : Country(mediator) {}

    void declare(std::string_view message) {
        mediator->declare(message, this);
    }

private:
    void get_message(std::string_view message) override {
        std::cout << "CHN GET MESSAGE: " << message << std::endl;
    }
};

// 联合国安理会，中介者，中介者类会越来越复杂，耦合所有业务逻辑
class UnitedNationsSecurityCouncil : public UnitedNations {
public:
    void set_USA(USA* nation) {
        America = nation;
    }

    void set_CHN(CHN* nation) {
        China = nation;
    }

private:
    void declare(std::string_view message, Country* colleague) override {   // 国家调用该方法进行交互
        if (colleague == America) {
            America->get_message(message);
        } else if (colleague == China) {
            China->get_message(message);
        }
    }

private:
    USA* America;
    CHN* China;
};

int main() {
    SetConsoleOutputCP(CP_UTF8);
    UnitedNationsSecurityCouncil* UNSC = new UnitedNationsSecurityCouncil();
    
    USA* usa = new USA(UNSC);
    CHN* chn = new CHN(UNSC);

    UNSC->set_USA(usa);
    UNSC->set_CHN(chn);

    usa->declare("我要侵略你们");
    chn->declare("来吧！犯我中华者，虽远必诛！");

    delete UNSC;
    delete usa;
    delete chn;

    return 0;
}