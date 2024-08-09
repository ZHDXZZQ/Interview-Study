/*
    命令模式Command： 将一个请求封装为一个对象，从而使你可用不同的请求对客户进行参数化，对请求进行排队或记录请求日志，以及支持可撤销的操作。
    优点：
        1. 能较为容易的设计一个命令队列
        2. 在需要的情况下，可以容易的将命令记入日志
        3. 允许接受请求的一方决定是否要否决请求
        4. 可以容易地实现对请求地撤销和重做
        5. 由于加进新的具体命令类不影响其他类，因此增加新的命令类很容易
        6. 把请求一个操作的对象与知道怎么执行一个操作的对象解耦

    敏捷开发原则说，不要为代码添加基于猜测的，实际不需要地功能。
    如果不清楚一个系统是否需要命令原则，一般不要着急实现。
    事实上，在需要的时候通过重构实现命令模式不难，只有在真正需要撤销/恢复操作等功能时，重构为命令模式才有意义。
*/

#include <iostream>

// Command用来声明执行操作的接口
class Command {
public:
    Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() = default;
};

// receiver类，知道如何执行操作
class Light {
public:
    void on() {
        std::cout << "The light is on" << std::endl;
    }
    
    void off() {
        std::cout << "The light is off" << std::endl;
    }
};

// concrete command类，将一个接收者对象绑定一个动作，调用接收者相应的操作
class LightOnCommand : public Command {
private:
    Light* light;

public:
    LightOnCommand(Light* light) : light(light) {}

    void execute() override {
        std::cout << "INFO: execute:";
        light->on();
    }

    void undo() override {
        std::cout << "WARNING: undo:";
        light->off();
    }
};

class LightOffCommand : public Command {
private:
    Light* light;

public:
    LightOffCommand(Light* light) : light(light) {}

    void execute() override {
        std::cout << "INFO: execute:";
        light->off();
    }

    void undo() override {
        std::cout << "WARNING: undo:";
        light->on();
    }
};

// Invoker类，要求该命令执行这个请求
class RemoteControl {
private:
    Command* command;

public:
    void setCommand(Command* command) {
        this->command = command;
    }

    void pressButton() {
        if (command) {
            command->execute();
        }
    }

    void pressUndoButton() {
        if (command) {
            command->undo();
        }
    }
};

int main() {
    // 创建接收者对象
    Light* livingRoomLight = new Light();

    // 创建具体命令对象
    LightOnCommand* lightOn = new LightOnCommand(livingRoomLight);
    LightOffCommand* lightOff = new LightOffCommand(livingRoomLight);

    // 创建调用者并设置命令
    RemoteControl* on_remote = new RemoteControl();
    RemoteControl* off_remote = new RemoteControl();
    on_remote->setCommand(lightOn);
    off_remote->setCommand(lightOff);

    // 测试命令
    on_remote->pressButton();  // The light is on
    off_remote->pressButton(); // The light is off
    off_remote->pressUndoButton(); // The light is on (撤销上次关灯操作)

    // 清理内存
    delete on_remote;
    delete off_remote;
    delete lightOn;
    delete lightOff;
    delete livingRoomLight;

    return 0;
}

