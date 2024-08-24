/*
    组合模式：Compoiste：将对象组合成树形结构以表示“部分-整体”的层次结构。组合模式使得用户对单个对象和组合对象的使用具有一致性。
    当需求中是体现部分与整体层次的结构时，并且希望用户可以忽略组合对象与单个对象的不同，统一地使用组合结构中的所有对象时，可以使用组合模式。

    leaf作为基本对象，可以被组合成更为复杂的组合对象，而这个组合对象也可以被组合，这样递归下来，客户代码中任何用到基本对象的地方都可以使用组合对象。

    透明方式：component中声明所有用来管理子对象的方法，这样所有子类都有这些接口，叶节点和枝节点就没有区别了，但是leaf本身不需要add和remove，因此没有意义。
    安全方式：在component接口不声明add和remove等方法，那么子类的leaf无需实现，而是在composite枝节点声明所有用来管理子类对象的方法，但是树叶和树枝有不同的接口，客户调用要做相应的判断
*/

#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

// component为组合中的对象声明接口，在适当情况下，实现所有类共有接口的默认行为。
// 同时声明接口用于访问和管理子部件。
class Company {
public:
    Company(string name) : name(name) {}

    virtual void add(Company* c) = 0;
    virtual void remove(Company* c) = 0;
    virtual void display(int depth) = 0;
    virtual void process() = 0;
protected:
    string name;
};

// composite定义有枝节点行为，用来存储子部件。在component接口中实现与子部件有关的操作。
class ConcreteCompany : public Company {
public:
    ConcreteCompany(string name) : Company(name) {}

    void add(Company* c) override {
        children.insert(c);
    }

    void remove(Company* c) override {
        children.erase(c);
    }

    void display(int depth) override {
        cout << string(depth, '-') << name << endl;
        for (auto company : children) {
            company->display(depth + 2);
        }
    }

    void process() override {
        for (auto company : children) {
            company->process();
        }
    }

private:
    unordered_set<Company*> children;
};

// leaf在组合中表示叶节点对象，没有子节点。
class HRDepartment : public Company {
public:
    HRDepartment(string name) : Company(name) {}
    void add(Company* c) override {}
    void remove(Company* c) override {}
    void display(int depth) override {
        cout << string(depth, '-') << name << endl;
    }

    void process() override {
        cout << name << " 招聘培训管理" << endl;
    }
};

class FinanceDepartment : public Company {
public:
    FinanceDepartment(string name) : Company(name) {}
    void add(Company* c) override {}
    void remove(Company* c) override {}
    void display(int depth) override {
        cout << string(depth, '-') << name << endl;
    }

    void process() override {
        cout << name << " 财务收支管理" << endl;
    }
};

int main() {
    ConcreteCompany* root = new ConcreteCompany("北京总部");
    root->add(new HRDepartment("总部人力资源部"));
    root->add(new FinanceDepartment("总部财务部"));

    ConcreteCompany* comp = new ConcreteCompany("上海分部");
    comp->add(new HRDepartment("上海分部人力资源部"));
    comp->add(new FinanceDepartment("上海分部财务部"));
    root->add(comp);

    ConcreteCompany* comp1 = new ConcreteCompany("南京办事处");
    comp1->add(new HRDepartment("南京办事处人力资源部"));
    comp1->add(new FinanceDepartment("南京办事处财务部"));
    comp->add(comp1);

    ConcreteCompany* comp2 = new ConcreteCompany("杭州办事处");
    comp2->add(new HRDepartment("杭州办事处人力资源部"));
    comp2->add(new FinanceDepartment("杭州办事处财务部"));
    comp->add(comp2);

    cout << "结构图：" << endl;
    root->display(1);

    cout << endl;

    cout << "职责：" << endl;
    root->process();    
    return 0;
}