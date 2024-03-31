#include <iostream>

class product {     //虚基类
public:
    virtual void use() = 0;
};

class WeChat : public product { //继承虚基类，即工厂的产品类
public:
    void use() {    //重写纯虚函数
        std::cout << "use we xin" << std::endl;
    }
};

class AliPay : public product { //第二个产品
public:
    void use() {
        std::cout << "use zhi fu bao" << std::endl;
    }
};

class Factory {
public:
    product* use_product(std::string type) {
        if (type == "zfb") {    //根据传入的类型选择对应的类创建实例并返回指针，返回类型为虚基类的指针
            return new AliPay();
        } else if (type == "wx") {
            return new WeChat();
        } else {
            return nullptr;
        }
    }
};  //这样可以通过类型直接获取相应的方法，而无需分别创建类

int main() {
    auto factory = new Factory();
    auto cur_product = factory->use_product("zfb");
    cur_product->use();
    return 0;
}