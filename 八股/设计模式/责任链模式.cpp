/*
    职责链模式：使多个对象都有机会处理请求，从而避免请求的发送者和接收者之间的耦合关系。
    将这个对象连成一条链，并沿着这条链传递该请求，直到有一个对象处理它为止。
    接收者和发送者都没有对方的明确信息，链中的对象也不知道链的结构，仅了解上下级。
*/

#include <iostream>
#include <string>

// 请求类
class Request {
public:
    std::string req_type;   // 请求类型
    std::string req_ctx;    // 请求上下文
    int number;             // 请求内容的数量
};

// 管理者基类
class Manager {
public:
    Manager() = delete;     // 必须设置管理者姓名
    Manager(std::string name) : name(name), leader(nullptr) {}
    void set_leader(Manager* leader) {  // 设置该管理者的上级
        this->leader = leader;
    }
    virtual void handler (Request* req) = 0;    // 处理请求
protected:
    std::string name;
    Manager* leader;
};

// 管理者具体类，小组长
class TeamLeader : public Manager {
public:
    TeamLeader(std::string name) : Manager(name) {}
    void handler(Request* req) override {
        if (req->req_type == "请假" && req->number <= 7) {  // 小组长只有权批准7天及以内的请假
            std::cout << name << ": " << req->req_ctx << req->number << "天 被批准" << std::endl; 
        } else {    // 其他情况直接请求上级
            if (leader != nullptr) {
                leader->handler(req);
            } else {
                std::cout << req->req_ctx << req->number << " 因上级离职无法处理,请联系领导重新设置上级" << std::endl;
            }
        }
    }
};

// 部门主管
class DepartmentHead : public Manager {
public:
    DepartmentHead(std::string name) : Manager(name) {}
    void handler(Request* req) override {
        if (req->req_type == "请假" && req->number <= 30) { // 部门主管只有权批准30天内的请假
            std::cout << name << ": " << req->req_ctx << req->number << "天 被批准" << std::endl; 
        } else if (req->req_type == "加薪" && req->number <= 6000) {    //以及6000元内的加薪
            std::cout << name << ": " << req->req_ctx << req->number << "元 被批准" << std::endl; 
        } else {
            if (leader != nullptr) {
                leader->handler(req);
            } else {
                std::cout << req->req_ctx << req->number << " 因上级离职无法处理,请联系领导重新设置上级" << std::endl;
            }
        }
    }
};

// 大boss
class Boss : public Manager {
public:
    Boss(std::string name) : Manager(name) {}
    void handler(Request* req) override {
        if (req->req_type == "请假" && req->number <= 90) { // boss会批准90天内的请假
            std::cout << name << ": " << req->req_ctx << req->number << "天 被批准" << std::endl; 
        } else if (req->req_type == "加薪" && req->number <= 10000) {   // 和10000元内的加薪
            std::cout << name << ": " << req->req_ctx << req->number << "元 被批准" << std::endl; 
        } else {    // 其余不批准
            std::cout << name << "不批准 " << req->req_ctx << req->number << std::endl;
        }
    }
};

int main() {
    TeamLeader* tl = new TeamLeader("小组长");
    DepartmentHead* dh = new DepartmentHead("部门主管");
    Boss* boss = new Boss("大领导");
    dh->set_leader(boss);

    Request* request = new Request();
    request->req_ctx = "小张申请请假 ";
    request->req_type = "请假";
    request->number = 5;
    tl->handler(request);

    request->number = 15;
    tl->handler(request);

    tl->set_leader(dh);
    tl->handler(request);

    request->number = 32;
    tl->handler(request);

    request->number = 108;
    tl->handler(request);

    request->req_ctx = "小王申请加薪 ";
    request->req_type = "加薪";
    request->number = 500;
    tl->handler(request);

    request->number = 4000;
    tl->handler(request);

    request->number = 6200;
    tl->handler(request);

    request->number = 10888;
    tl->handler(request);

    delete request;
    return 0;
}