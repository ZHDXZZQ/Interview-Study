/*
    享元模式FlyWeight：运用共享技术有效地支持大量细粒度的对象。
    享元模式可以避免大量非常相似类的开销。
    使用场景：一个应用程序使用了大量的对象，而大量的这些对象造成了很大的存储开销时
             或者对象的大多数状态为外部状态，如果删除对象的外部状态，那么可以用相对较少的共享对象取代很多组对象。
*/

#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

// 用户类：用于网站的客户账号，是网站类的外部状态
class User {
public:
    User(string name) : name(name) {}
    string get_name() {
        return name;
    }
private:
    string name;
};

// 网站抽象类
class WebSite {
public:
    virtual void Use(User* user) = 0;
};

// 具体某个网站，即内在状态，避免多个网站写多个类
class ConcreteWebSite : public WebSite {
public:
    ConcreteWebSite(string name) : name(name) {}
    void Use(User* user) override {
        cout << "网站分类： " << name << "， 用户： " << user->get_name() << endl;
    }
private:
    string name;
};

// 网站工厂类，避免每次创建新对象，全局唯一，单例
class WebSiteFactory {
public:
    static WebSiteFactory* get_instance();

    ConcreteWebSite* get_website_category(string key) { // 应该用类型转换返回WebSite类型的指针
        if (umap.find(key) == umap.end()) {
            umap[key] = new ConcreteWebSite(key);
        }
        return umap[key];
    }

    int get_website_count() {
        return umap.size();
    }
private:
    static WebSiteFactory *p;
    WebSiteFactory() {}
    ~WebSiteFactory() {}
    unordered_map<string, ConcreteWebSite*> umap;
};

// 应用饿汉单例模式
WebSiteFactory* WebSiteFactory::p = new WebSiteFactory();   //启动时初始化，可以调用私有函数？
WebSiteFactory* WebSiteFactory::get_instance() {
    return p;
}

// 客户代码
int main() {
    WebSiteFactory* f = WebSiteFactory::get_instance();

    WebSite* fx = f->get_website_category("产品展示");
    fx->Use(new User("小菜"));

    WebSite* fy = f->get_website_category("产品展示");
    fx->Use(new User("大鸟"));

    WebSite* fz = f->get_website_category("博客");
    fx->Use(new User("老顽童"));
    
    cout << "网站分类总数为 ： " << f->get_website_count() << endl;

    return 0;
}

// 虽然有3个用户访问了网站，但是只有两个不同的分类，因此共享了同一个“产品展示”类的网站对象，减少了对象的创建开销。
// 工厂中只创建了两个不同的 WebSite 对象，一个是“产品展示”，另一个是“博客”。