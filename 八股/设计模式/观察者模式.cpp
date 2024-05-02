/*
    观察者模式：发布-订阅模式：定义了一种一对多的依赖关系
    让多个观察者对象同时监听某一个主题对象。这个主题对象在状态发生变化时，
    会通知所有观察者对象，使得他们能够自动更新自己。
*/

#include <iostream>
#include <unordered_set>
#include <string>

// 观察者基类，观察目标的情况来更新自己
class Observer {
public:
    virtual void update(std::string condition) = 0;
};

// 观察主题，每个主题存有多个观察者，在状态发生变化时，通知所有观察者
class Subject {
public:
    virtual void attach(Observer* ob) = 0;
    virtual void detach(Observer* ob) = 0;
    virtual void notify() = 0;
};

// 老板视察类，作为一个主题
class BossInspect : public Subject {
public:
    BossInspect(std::string status = "老板不在") : boss_status(status) {}
    void attach(Observer* ob) override {
        obs.insert(ob);
    }
    void detach(Observer* ob) override {
        if (obs.find(ob) != obs.end()) {
            obs.erase(ob);
        }
    }
    void notify() override {    //同志所有员工老板当前的状态
        for (auto& ob : obs) {
            ob->update(boss_status);
        }
    }
    void change_status(std::string status) {    //老板改变状态时，通知员工
        boss_status = status;
        std::cout << status << std::endl;
        notify();
    }
private:
    std::string boss_status;
    std::unordered_set<Observer*> obs;
};

// 观察者类，员工观看NBA
class WatchNBAer : public Observer {
public:
    WatchNBAer(std::string name, std::string status, Subject* sub) : 
                name(name), worker_status(status), sub(sub) {
        sub->attach(this);  //将员工加入需要观察的主题
    }
    ~WatchNBAer() {
        sub->detach(this);
    }
    void update(std::string condition) override {   //在有通知时，更新员工的状态
        if (condition == "老板来了") {
            worker_status = "工作中";
            std::cout << "员工: " << name << " 正在工作中 !" << std::endl; 
        } else {
            worker_status = "摸鱼看NBA";
            std::cout << "员工: " << name << " 开始摸鱼看NBA !" << std::endl; 
        }
    }

private:
    std::string name;
    std::string worker_status;
    Subject* sub;
};

int main() {
    BossInspect* boss = new BossInspect();
    WatchNBAer* a = new WatchNBAer("小黄", "摸鱼看NBA", boss);
    WatchNBAer* b = new WatchNBAer("小张", "摸鱼看NBA", boss);
    boss->change_status("老板来了");
    boss->change_status("老板走了");
    return 0;
}