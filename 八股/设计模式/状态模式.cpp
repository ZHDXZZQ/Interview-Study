/*
    面向对象的思想就是希望代码的责任分解
    状态模式State：当一个对象的内在状态改变时，允许改变其行为，这个对象看起来像是改变了其类。
    状态模式主要解决的是当控制一个对象状态转换的条件表达式过于复杂时的情况。
    把状态的判断逻辑转移到表示不同状态的一系列类当中，可以把复杂的判断逻辑简化。
    当然，如果这个状态判断很简单，就没必要用状态模式了。

    状态模式的好处是将与特定状态相关的行为局部化，并且将不同状态的行为分割开来。
    将特定的状态相关的行为都放入一个对象中，由于所有与状态相关的代码都存在于某个ConcreteState中，所以通过定义新的子类可以很容易地增加新的状态和转换。
    目的就是为了消除庞大的条件分支语句，大的分支判断会使得它们难以修改和扩展，就像我们最早说的刻版印刷一样，任何改动和变化都是致命的。
    状态模式通过把各种状态转移逻辑分布到State的子类之间，来减少相互间的依赖，好比把整个版面改成了一个又一个的活字，此时就容易维护和扩展了。

    当一个对象的行为取决于它的状态，并且它必须在运行时刻根据状态改变它的行为时，就可以考虑使用状态模式了。
    另外如果业务需求某项业务有多个状态，通常都是一些枚举常量，状态的变化都是依靠大量的多分支判断语句来实现，此时应该考虑将每一种业务状态定义为一个State的子类。
    这样这些对象就可以不依赖于其他对象而独立变化了，某一天客户需要更改需求，增加或减少业务状态或改变状态流程就容易了。
*/

#include <iostream>
#include <memory>

class Light;

// 抽象状态类接口
class State {
public:
    virtual ~State() = default;
    virtual void pressSwitch(Light& light) = 0; // 每个状态要对具体的上下文对象情况做出操作调整状态
};

// 具体状态类，开灯状态，因为用到了上下文类的方法所以后面再定义内容
class OnState : public State {
public:
    void pressSwitch(Light& light) override;
};

// 具体状态类，关灯状态
class OffState : public State {
public:
    void pressSwitch(Light& light) override;
};

// 上下文类，实际操作状态，存储当前对象的各种标志，以供具体的状态类来调整实际状态
class Light {
public:
    Light(std::unique_ptr<State> initialState) : state(std::move(initialState)) {}

    void setState(std::unique_ptr<State> newState) {    // 由子类实际操作状态
        state = std::move(newState);
    }

    void pressSwitch() {    // 调用子类状态函数来改变当前状态
        state->pressSwitch(*this);
    }

private:    // 还可以存储一下标志用于各种状态子类判断下一步要进行的操作
    std::unique_ptr<State> state;   // 当前状态子类
};

void OnState::pressSwitch(Light& light) {
    std::cout << "Turning off the light." << std::endl;
    light.setState(std::make_unique<OffState>());   // 改变状态
}

void OffState::pressSwitch(Light& light) {
    std::cout << "Turning on the light." << std::endl;
    light.setState(std::make_unique<OnState>());
}

int main() {
    Light light(std::make_unique<OffState>());  // 初始化为关灯状态
    light.pressSwitch(); // Turning on the light.
    light.pressSwitch(); // Turning off the light.
    light.pressSwitch(); // Turning on the light.

    return 0;
}
