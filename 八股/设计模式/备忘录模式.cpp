/*
    备忘录模式：Memento。在不破坏封装性的前提下，捕获一个对象的内部状态，并在该对象之外保存这个状态
    这样以后就可以将该对象恢复到原先保存的状态。
    Originator发起人：负责创建一个备忘录Memento，记录当前时刻它的内部状态，并可使用备忘录恢复内部状态。
    Menmento备忘录：负责存储Originator的内部状态，并可防止Originator以外的对象访问备忘录。
    Caretaker管理者：负责保存备忘录，不能对备忘录的内容操作或检查。
    窄接口：管理者将备忘录传递给其他对象。
    宽接口：发起人允许它返回到先前状态所需的所有数据。
*/

#include <iostream>
#include <string>
#include <windows.h> // 仅适用于 Windows 系统

// 备忘录，用于记录当前角色的三个状态，可以支持设置和读取
class RoleStateMemento {
public:
    RoleStateMemento(int hp, int atk, int def) : hp_(hp), atttack_(atk), defence_(def) {}
    void set_hp(int new_hp) {
        hp_ = new_hp;
    }
    int get_hp() {
        return hp_;
    }
    void set_atk(int new_atk) {
        atttack_ = new_atk;
    }
    int get_atk() {
        return atttack_;
    }
    void set_def(int new_def) {
        defence_ = new_def;
    }
    int get_def() {
        return defence_;
    }
private:
    int hp_;
    int atttack_;
    int defence_;
};

// 角色，可以记录角色的姓名、生命、攻击、防御
class Role {
public:
    Role(std::string name, int hp, int atk, int def) : name_(name), hp_(hp), atk_(atk), def_(def) {}
    RoleStateMemento* save_state() {    // 记录当前状态
        return new RoleStateMemento(hp_, atk_, def_);
    }
    void recovery_state(RoleStateMemento* memento) {    // 恢复之前的某个状态
        hp_ = memento->get_hp();
        atk_ = memento->get_atk();
        def_ = memento->get_def();
    }
    void show() {   // 展示当前状态
        std::cout<< "英雄：" << name_ << ", 血量：" << hp_ << "， 攻击力：" << atk_ << "， 防御：" << def_ << std::endl;
    }
    void fight() {  // 可以设计传入一个对象，对本英雄造成伤害
        hp_ -= 22;
        def_ -= 12;
        atk_ -= 17;
    }
private:
    std::string name_;
    int hp_;
    int atk_;
    int def_;
};

// 管理者，用于存储状态，以及恢复状态
class RoleStateCaretaker {
public:
    RoleStateMemento* get_memory() {
        return memento_;
    }
    void set_memory(RoleStateMemento* memento) {
        memento_ = memento;
    }
private:
    RoleStateMemento* memento_;
};

int main() {
    // 设置控制台输出的编码为UTF-8
    SetConsoleOutputCP(CP_UTF8);
    
    // 初始化英雄
    Role* dijia = new Role("迪迦", 50, 77, 23);
    dijia->show();

    // 保存当前的状态
    RoleStateCaretaker* state1 = new RoleStateCaretaker();
    state1->set_memory(dijia->save_state());

    // 战斗
    dijia->fight();
    dijia->show();

    // 恢复之前状态
    dijia->recovery_state(state1->get_memory());
    dijia->show();
    return 0;
}