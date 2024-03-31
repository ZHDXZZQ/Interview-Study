// 实现基本的vector接口
// 实现了几个重要的结构：三种构造函数，获取size，获取容器大小，尾插、尾删、判空、重设容器空间、重载[]运算符
// 没有实现迭代器的接口
// reverse和opeator[]是重点

#include <iostream>

template<typename T>
class MyVector {
private:
    T* data;            //实际的底层数组
    size_t size;        //指向当前数组的尾部的下一个
    size_t capacity;    //当前数组可用地址空间的大小

public:
    MyVector() : capacity(10), size(0) {
        data = new T[capacity];
    }

    MyVector(size_t init_size) : capacity(init_size), size(10) {    //初始化vector大小，默认赋值0
        data = new T[capacity];
        for (auto i = 0; i < init_size; ++ i) {
            data[i] = 0;
        }
    }

    MyVector(size_t init_size, T init_val) : capacity(init_size), size(10) {    //初始化vector大小和初值
        data = new T[capacity];
        for (auto i = 0; i < init_size; ++ i) {
            data[i] = init_val;
        }
    }

    ~MyVector() {
        delete[] data;
    }

    size_t getSize() const {
        return size;
    }

    size_t getCapacity() const {
        return capacity;
    }

    bool empty() {
        if (size == 0) {
            return true;
        }
        return false;
    }

    void reserve(size_t new_capacity) {
        if (new_capacity > capacity) {
            T* new_data = new T[new_capacity];
            for (auto i = 0; i < size; ++ i) {
                new_data[i] = data[i];
            }
            delete[] data;
            data = new_data;
            capacity = new_capacity;
        }
    }

    void push_back(const T value) {
        if (size >= capacity) {
            // 扩容
            size_t new_capacity = capacity == 0 ? 1 : capacity * 2;
            this->reserve(new_capacity);
        }
        data[size++] = value;   //
    }

    void pop_back() {
        if (size == 0) {
            throw std::out_of_range("删除失败，不能对空MyVector进行删除操作");
        }
        -- size;
    }

    T& operator[](size_t index) {
        if (index >= size || index < 0) {
            throw std::out_of_range("访问MyVector的下标超出范围");
        }
        return data[index];
    }
};