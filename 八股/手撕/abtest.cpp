#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <random>  // For random number generation

/*------------------------------随机数实现---------------------------*/

// 策略接口类
class GroupStrategy {
public:
    virtual ~GroupStrategy() = default;
    virtual std::string executeLogic() const = 0;
};

// 组 A 的具体策略
class GroupAStrategy : public GroupStrategy {
public:
    std::string executeLogic() const override {
        return "Logic of Group A executed!";
    }
};

// 组 B 的具体策略
class GroupBStrategy : public GroupStrategy {
public:
    std::string executeLogic() const override {
        return "Logic of Group B executed!";
    }
};

// 组 C 的具体策略
class GroupCStrategy : public GroupStrategy {
public:
    std::string executeLogic() const override {
        return "Logic of Group C executed!";
    }
};

// 策略工厂类
class GroupStrategyFactory {
public:
    static std::unique_ptr<GroupStrategy> createStrategy(int groupId) {
        switch (groupId) {
            case 0: return std::make_unique<GroupAStrategy>();
            case 1: return std::make_unique<GroupBStrategy>();
            case 2: return std::make_unique<GroupCStrategy>();
            default: throw std::invalid_argument("Unknown group ID");
        }
    }
};

// 流量分配器，使用随机数生成器进行分组
std::string abTestTrafficSplit(const std::string& userId, const std::vector<int>& groupWeights) {
    // 计算总流量百分比的累积分布
    std::vector<int> cumulativeWeights;
    int total = 0;
    for (int weight : groupWeights) {
        total += weight;
        cumulativeWeights.push_back(total);
    }

    // 校验总和是否为 100
    if (total != 100) {
        throw std::invalid_argument("The total percentage must be 100%.");
    }

    // 生成一个0到99的随机数
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 99);
    int randomValue = distrib(gen);
    std::cout << randomValue << std::endl;

    // 按照累积流量区间分配到各组
    for (size_t i = 0; i < cumulativeWeights.size(); ++i) {
        if (randomValue < cumulativeWeights[i]) {
            // 通过工厂模式创建策略并执行逻辑
            auto strategy = GroupStrategyFactory::createStrategy(i);
            return strategy->executeLogic();
        }
    }
    return "No Group Assigned";  // 异常情况
}

int main() {
    // 设置每组的流量比例 (如：50% A组, 30% B组, 20% C组)
    std::vector<int> groupWeights = {50, 30, 20};

    // 测试不同用户的分流
    std::string userId1 = "user123";
    std::string userId2 = "user456";
    std::string userId3 = "user789";

    // 打印每个用户分到的组及其对应逻辑
    std::cout << userId1 << ": " << abTestTrafficSplit(userId1, groupWeights) << std::endl;
    std::cout << userId2 << ": " << abTestTrafficSplit(userId2, groupWeights) << std::endl;
    std::cout << userId3 << ": " << abTestTrafficSplit(userId3, groupWeights) << std::endl;

    return 0;
}


/*-------------------------哈希实现------------------------*/

#include <iostream>
#include <string>
#include <vector>
#include <memory>  // For smart pointers

// 策略接口类
class GroupStrategy {
public:
    virtual ~GroupStrategy() = default;
    virtual std::string executeLogic() const = 0;
};

// 组 A 的具体策略
class GroupAStrategy : public GroupStrategy {
public:
    std::string executeLogic() const override {
        return "Logic of Group A executed!";
    }
};

// 组 B 的具体策略
class GroupBStrategy : public GroupStrategy {
public:
    std::string executeLogic() const override {
        return "Logic of Group B executed!";
    }
};

// 组 C 的具体策略
class GroupCStrategy : public GroupStrategy {
public:
    std::string executeLogic() const override {
        return "Logic of Group C executed!";
    }
};

// 策略工厂类
class GroupStrategyFactory {
public:
    static std::unique_ptr<GroupStrategy> createStrategy(int groupId) {
        switch (groupId) {
            case 0: return std::make_unique<GroupAStrategy>();
            case 1: return std::make_unique<GroupBStrategy>();
            case 2: return std::make_unique<GroupCStrategy>();
            default: throw std::invalid_argument("Unknown group ID");
        }
    }
};

// 流量分配器
std::string abTestTrafficSplit(const std::string& userId, const std::vector<int>& groupWeights) {
    // 计算总流量百分比的累积分布
    std::vector<int> cumulativeWeights;
    int total = 0;
    for (int weight : groupWeights) {
        total += weight;
        cumulativeWeights.push_back(total);
    }

    // 校验总和是否为 100
    if (total != 100) {
        throw std::invalid_argument("The total percentage must be 100%.");
    }

    // 使用哈希函数生成随机值（可以改为随机数生成器）
    std::hash<std::string> hash_fn;
    size_t hashedValue = hash_fn(userId);
    int randomValue = hashedValue % 100;  // 0 到 99 之间的值

    // 按照累积流量区间分配到各组
    for (size_t i = 0; i < cumulativeWeights.size(); ++i) {
        if (randomValue < cumulativeWeights[i]) {
            // 通过工厂模式创建策略并执行逻辑
            auto strategy = GroupStrategyFactory::createStrategy(i);
            return strategy->executeLogic();
        }
    }
    return "No Group Assigned";  // 异常情况
}

int main() {
    // 设置每组的流量比例 (如：50% A组, 30% B组, 20% C组)
    std::vector<int> groupWeights = {50, 30, 20};

    // 测试不同用户的分流
    std::string userId1 = "user123";
    std::string userId2 = "user456";
    std::string userId3 = "user789";

    // 打印每个用户分到的组及其对应逻辑
    std::cout << userId1 << ": " << abTestTrafficSplit(userId1, groupWeights) << std::endl;
    std::cout << userId2 << ": " << abTestTrafficSplit(userId2, groupWeights) << std::endl;
    std::cout << userId3 << ": " << abTestTrafficSplit(userId3, groupWeights) << std::endl;

    return 0;
}


/*------------------------全局变量实现---------------------------------*/
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <mutex>  // For thread-safe counter

// 策略接口类
class GroupStrategy {
public:
    virtual ~GroupStrategy() = default;
    virtual std::string executeLogic() const = 0;
};

// 组 A 的具体策略
class GroupAStrategy : public GroupStrategy {
public:
    std::string executeLogic() const override {
        return "Logic of Group A executed!";
    }
};

// 组 B 的具体策略
class GroupBStrategy : public GroupStrategy {
public:
    std::string executeLogic() const override {
        return "Logic of Group B executed!";
    }
};

// 组 C 的具体策略
class GroupCStrategy : public GroupStrategy {
public:
    std::string executeLogic() const override {
        return "Logic of Group C executed!";
    }
};

// 策略工厂类
class GroupStrategyFactory {
public:
    static std::unique_ptr<GroupStrategy> createStrategy(int groupId) {
        switch (groupId) {
            case 0: return std::make_unique<GroupAStrategy>();
            case 1: return std::make_unique<GroupBStrategy>();
            case 2: return std::make_unique<GroupCStrategy>();
            default: throw std::invalid_argument("Unknown group ID");
        }
    }
};

// 全局计数器
int counter = 0;
// 互斥锁，用于保护 counter
std::mutex counterMutex;

// 流量分配器，基于循环递增的计数器进行分组
std::string abTestTrafficSplit(const std::vector<int>& groupWeights) {
    // 计算总流量百分比的累积分布
    std::vector<int> cumulativeWeights;
    int total = 0;
    for (int weight : groupWeights) {
        total += weight;
        cumulativeWeights.push_back(total);
    }

    // 校验总和是否为 100
    if (total != 100) {
        throw std::invalid_argument("The total percentage must be 100%.");
    }

    // 获取并递增全局计数器
    int currentCounter;
    {
        std::lock_guard<std::mutex> lock(counterMutex);  // 保证线程安全
        currentCounter = counter;
        counter = (counter + 1) % 100;  // 计数器从 0-99 循环
    }

    // 按照累积流量区间分配到各组
    for (size_t i = 0; i < cumulativeWeights.size(); ++i) {
        if (currentCounter < cumulativeWeights[i]) {
            // 通过工厂模式创建策略并执行逻辑
            auto strategy = GroupStrategyFactory::createStrategy(i);
            return strategy->executeLogic();
        }
    }
    return "No Group Assigned";  // 异常情况
}

int main() {
    // 设置每组的流量比例 (如：50% A组, 30% B组, 20% C组)
    std::vector<int> groupWeights = {50, 30, 20};

    // 模拟多次分流操作
    for (int i = 0; i < 10; ++i) {
        std::cout << "User " << i << ": " << abTestTrafficSplit(groupWeights) << std::endl;
    }

    return 0;
}
