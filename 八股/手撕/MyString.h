#include <iostream>
#include <cstring>

class MyString {
private:
    char* data; // 存储字符串
    size_t len; // 字符串长度

public:
    // 默认构造函数
    MyString() : data(nullptr), len(0) {
        data = new char[1];
        data[0] = '\0';
    }

    // 带参构造函数
    MyString(const char* str) {
        if (str) {
            len = std::strlen(str);
            data = new char[len + 1];
            std::strcpy(data, str);
        } else {
            data = new char[1];
            data[0] = '\0';
            len = 0;
        }
    }

    // 拷贝构造函数
    MyString(const MyString& other) {
        len = other.len;
        data = new char[len + 1];
        std::strcpy(data, other.data);
    }

    // 赋值运算符
    MyString& operator=(const MyString& other) {
        if (this == &other) {
            return *this; // 自赋值保护
        }

        // 释放原有的资源
        delete[] data;

        // 分配新空间并拷贝数据
        len = other.len;
        data = new char[len + 1];
        std::strcpy(data, other.data);

        return *this;
    }

    // 返回字符串长度
    size_t length() const {
        return len;
    }

    // 返回C风格字符串
    const char* c_str() const {
        return data;
    }

    // 析构函数，释放内存
    ~MyString() {
        delete[] data;
    }
};