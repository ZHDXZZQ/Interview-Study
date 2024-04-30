#include <iostream>

// 抽象策略类
class PricingStrategy {
public:
    virtual double calculatePrice(double price) const = 0;
};

// 具体策略类：普通会员价格计算策略
class RegularPricingStrategy : public PricingStrategy {
public:
    double calculatePrice(double price) const override {
        return price;
    }
};

// 具体策略类：高级会员价格计算策略
class PremiumPricingStrategy : public PricingStrategy {
public:
    double calculatePrice(double price) const override {
        return price * 0.9; // 打九折
    }
};

// 具体策略类：超级会员价格计算策略
class SuperPremiumPricingStrategy : public PricingStrategy {
public:
    double calculatePrice(double price) const override {
        return price * 0.8; // 打八折
    }
};

// 上下文类：价格计算器
class PriceCalculator {
private:
    const PricingStrategy *strategy;

public:
    PriceCalculator(const PricingStrategy *strategy) : strategy(strategy) {}

    void setStrategy(const PricingStrategy *strategy) {
        this->strategy = strategy;
    }

    double calculatePrice(double price) const {
        return strategy->calculatePrice(price);
    }
};

int main() {
    // 创建不同的价格计算策略
    const PricingStrategy *regularStrategy = new RegularPricingStrategy();
    const PricingStrategy *premiumStrategy = new PremiumPricingStrategy();
    const PricingStrategy *superPremiumStrategy = new SuperPremiumPricingStrategy();

    // 创建价格计算器，并设置不同的策略
    PriceCalculator calculator(regularStrategy);
    std::cout << "Regular member price: " << calculator.calculatePrice(100) << std::endl;

    calculator.setStrategy(premiumStrategy);
    std::cout << "Premium member price: " << calculator.calculatePrice(100) << std::endl;

    calculator.setStrategy(superPremiumStrategy);
    std::cout << "Super premium member price: " << calculator.calculatePrice(100) << std::endl;

    // 释放资源
    delete regularStrategy;
    delete premiumStrategy;
    delete superPremiumStrategy;

    return 0;
}
