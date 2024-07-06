/*
    代理模式Proxy：为其他对象提供一种代理以控制对这个对象的访问
    远程代理：为一个对象在不同的地址空间提供局部代表，这样可以隐藏一个对象存在于不同地址空间的事实
    虚拟代理：根据需要创建开销很大的对象，通常它来存放实例化需要很长时间的真实对象
    安全代理：用来控制真实对象访问时的权限
    智能指引：当调用真实的对象时，代理处理另外一些事
    简单理解就是我们在不认识对方的前提下，获取了对方的东西，而我们只通过了代理人获得了东西，但却不知对方的身份
*/

// 这个示例展示了如何使用代理模式来控制对资源密集型对象的访问，并延迟其加载，直到真正需要时再加载。

#include <iostream>
#include <string>

// Image接口，即Subject，定义了接口，由Proxy和RealSubject共用，保证任何需要实际调用的地方都可以通过代理实现
class Image {
public:
    virtual void display() = 0;
    virtual ~Image() {}
};

// RealImage类，实现Image接口
// 即RealSubject，定义了Proxy所代理的真实实体
class RealImage : public Image {
private:
    std::string filename;
    void loadFromDisk() {
        std::cout << "Loading " << filename << " from disk..." << std::endl;
    }

public:
    RealImage(const std::string& filename) : filename(filename) {
        loadFromDisk(); // 初始化时加载图像
    }

    void display() override {   // 真实的请求
        std::cout << "Displaying " << filename << std::endl;
    }
};

// ProxyImage类，实现Image接口
// 即Proxy代理类，保存一个真实实体的指针，这样可以通过代理的接口访问真实的接口
// 其作用可以让职责分离，让代理类提供统一的接口，并且代理类负责调用和逻辑检查、缓存等，而真实对象类只负责加载
class ProxyImage : public Image {
private:
    std::string filename;
    RealImage* realImage;

public:
    ProxyImage(const std::string& filename) : filename(filename), realImage(nullptr) {}

    ~ProxyImage() {
        delete realImage;
    }

    void display() override {
        if (realImage == nullptr) {
            realImage = new RealImage(filename); // 延迟加载图像
        }
        realImage->display();
    }
};

// 客户端代码
int main() {
    // 代理类的对象，真实的对象我们在代理内部创建，这里也可以用ProxyImage类而不是Image类
    // 此时默默创建对象，但是并没有着急加载，只在使用时再加载，避免不必要的资源浪费
    // 这里代理模式也可以控制对象的权限等
    Image* image = new ProxyImage("test_image.jpg");    

    // 图像将在首次调用display()时加载
    std::cout << "First call to display:" << std::endl;
    image->display();

    // 后续调用将不再加载图像
    std::cout << "Second call to display:" << std::endl;
    image->display();

    delete image;
    return 0;
}
