/*
    原型模式Prototype：用原型实例指定创建对象的种类，并且通过拷贝这些原型创建新的对象。
    就是从一个对象再创建另外一个可定制的对象，而且不需要知道任何创建的细节。
    涉及到部分指针和引用的深拷贝与浅拷贝。
    以下以简历的拷贝实现原型模式的示例。
*/

#include <iostream>
#include <string>
#include <memory>

using namespace std;

// 抽象基类 ResumePrototype，定义克隆方法
class ResumePrototype {
public:
    virtual ~ResumePrototype() {}
    // 克隆方法，返回指向自身副本的指针
    virtual ResumePrototype* clone() const = 0;
    virtual void show() const = 0;
};

// 工作经历类，深拷贝的应用
class WorkExperience {
public:
    WorkExperience(const string company_name, const string work_time) : company_name(company_name), work_time(work_time) {}
    WorkExperience(const WorkExperience* workexperience) {
        this->company_name = workexperience->company_name;
        this->work_time = workexperience->work_time;
    }
    void get_info() {
        cout << "公司名称是：" << company_name << "，工作时长为：" << work_time << endl;
    }
private:
    string company_name;
    string work_time;
};

// 具体原型类 Resume
class Resume : public ResumePrototype {
private:
    std::string name;
    std::string gender;
    WorkExperience* workexperience;
    // 私有方法，仅用于拷贝时可以调用workexperience的拷贝构造函数深度拷贝
    Resume(const std::string& name, const std::string& gender, WorkExperience* workexperience)
        : name(name), gender(gender) {
            this->workexperience = new WorkExperience(workexperience);
        }

public:
    Resume(const std::string& name, const std::string& gender, const string company_name, const string work_time)
        : name(name), gender(gender) {
            workexperience = new WorkExperience(company_name, work_time);
        }

    // 克隆方法，实现复制自身
    ResumePrototype* clone() const override {
        ResumePrototype* new_resume = new Resume(name, gender, workexperience);
        return new_resume;
    }

    // 显示简历信息
    void show() const override {
        std::cout << "Name: " << name << std::endl;
        std::cout << "Gender: " << gender << std::endl;
        workexperience->get_info();
    }

    // 修改工作经历
    void setExperience(WorkExperience* we) {
        workexperience = we;
    }
};

// 客户端代码
int main() {
    // 创建原始简历
    ResumePrototype* originalResume = new Resume("Alice", "Female", "xyz", "50days");

    // 复制简历
    ResumePrototype* clonedResume = originalResume->clone();

    // 显示原始简历
    std::cout << "Original Resume:" << std::endl;
    originalResume->show();

    // 修改克隆简历的工作经历
    WorkExperience* we = new WorkExperience("bytedance", "180days");
    dynamic_cast<Resume*>(clonedResume)->setExperience(we);

    // 显示克隆后的简历
    std::cout << "\nCloned Resume with modified experience:" << std::endl;
    clonedResume->show();

    // 再次显示原始简历，确认其未受影响
    std::cout << "\nOriginal Resume remains unchanged:" << std::endl;
    originalResume->show();

    return 0;
}
