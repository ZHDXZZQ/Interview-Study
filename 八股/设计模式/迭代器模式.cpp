/*
    迭代器模式Iterator：提供一种方法顺序的访问一个聚合对象中的各个元素，
    而又不暴露该对象的内部表示。
    它允许客户端通过统一的接口遍历集合中的元素，而不需要暴露集合的内部表示。
    比如我们常用的cpp中的vector等stl库容器都是迭代器的实现。
*/

#include <iostream>
#include <vector>

// 抽象迭代器接口
template<typename T>
class Iterator {
public:
    virtual bool hasNext() const = 0;
    virtual T next() = 0;
};

// 具体迭代器实现
template<typename T>
class VectorIterator : public Iterator<T> {
public:
    VectorIterator(const std::vector<T>& data, size_t index) : data(data), currentIndex(index) {}

    bool hasNext() const override {
        return currentIndex < data.size();
    }

    T next() override {
        return data[currentIndex++];
    }

private:
    const std::vector<T>& data;
    size_t currentIndex;
};

// 抽象容器接口
template<typename T>
class Aggregate {
public:
    virtual Iterator<T>* createIterator() const = 0;
    virtual Iterator<T>* begin() const = 0;
    virtual Iterator<T>* end() const = 0;
    virtual size_t size() const = 0;
    virtual T& operator[](size_t index) = 0;
};

// 具体容器实现
template<typename T>
class ConcreteAggregate : public Aggregate<T> {
public:
    ConcreteAggregate(const std::vector<T>& data) : data(data) {}

    Iterator<T>* createIterator() const override {
        return new VectorIterator<T>(data, 0);
    }

    Iterator<T>* begin() const override {
        return new VectorIterator<T>(data, 0);
    }

    Iterator<T>* end() const override {
        return new VectorIterator<T>(data, data.size());
    }

    size_t size() const override {
        return data.size();
    }

    T& operator[](size_t index) override {
        return data[index];
    }

private:
    std::vector<T> data;
};

int main() {
    std::vector<int> data;
    for (int i = 0; i < 5; ++ i) {
        data.push_back(i);
    }

    // 创建具体容器实例
    ConcreteAggregate<int> container(data);

    // 使用迭代器遍历容器中的元素
    Iterator<int>* it = container.createIterator();
    while (it->hasNext()) {
        std::cout << it->next() << " ";
    }
    std::cout << std::endl;

    // 使用 begin() 和 end() 方法遍历容器中的元素
    for (Iterator<int>* iter = container.begin(); iter != container.end(); ) {
        std::cout << iter->next() << " ";
    }
    std::cout << std::endl;

    delete it;

    // 使用容器的其他方法
    std::cout << "Container size: " << container.size() << std::endl;
    std::cout << "Element at index 2: " << container[2] << std::endl;

    return 0;
}
