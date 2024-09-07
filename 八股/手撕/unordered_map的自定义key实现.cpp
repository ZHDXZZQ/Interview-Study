// 1. Key
// 定义：unordered_map<Key, T>
// 作用：表示映射的键类型。例如，int、std::string 或自定义的类等。
// 2. T
// 定义：unordered_map<Key, T>
// 作用：表示映射的值类型。每个键对应一个值。
// 3. Hash
// 定义：unordered_map<Key, T, Hash>
// 作用：用于计算键的哈希值的函数对象。默认情况下使用 std::hash<Key>。如果 Key 是自定义类型且没有提供 std::hash 的特化，需要提供自定义的哈希函数。
// 4. KeyEqual
// 定义：unordered_map<Key, T, Hash, KeyEqual>
// 作用：用于比较两个键是否相等的函数对象。默认情况下使用 std::equal_to<Key>。如果 Key 是自定义类型，需要提供自定义的比较函数。
// 5. Allocator
// 定义：unordered_map<Key, T, Hash, KeyEqual, Allocator>
// 作用：用于分配内存的分配器。默认情况下使用 std::allocator<std::pair<const Key, T>>。可以提供自定义分配器来管理内存。

#include <iostream>
#include <unordered_map>
#include <string>
#include <cstring>

using namespace std;

// 定义类 C
class C {
public:
    int e;
    float f;

    C(int e = 0, float f = 0.0f) : e(e), f(f) {}
};

// 定义类 A
class A {
public:
    int x;
    float y;
    char z;
    char* a;
    string b;
    C c;

    A(int x = 0, float y = 0.0f, char z = '\0', const char* a = "", string b = "", C c = C())
        : x(x), y(y), z(z), b(b), c(c) {
        this->a = new char[strlen(a) + 1];  // char*要深拷贝
        strcpy(this->a, a); // 复制内容
    }

    // 拷贝构造函数
    A(const A& other) : x(other.x), y(other.y), z(other.z), b(other.b), c(other.c) {
        a = new char[strlen(other.a) + 1];
        strcpy(a, other.a);
    }

    // 重载赋值运算符
    A& operator=(const A& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
            z = other.z;
            b = other.b;
            c = other.c;
            delete[] a;
            a = new char[strlen(other.a) + 1];
            strcpy(a, other.a);
        }
        return *this;
    }

    ~A() {
        delete[] a;
    }

    bool operator==(const A& other) const {
        return x == other.x && y == other.y && z == other.z && strcmp(a, other.a) == 0 && b == other.b && c.e == other.c.e && c.f == other.c.f;
    }
};

// 自定义哈希函数
namespace std {
    template <>
    struct hash<A> {    // 全特化哈希函数
        size_t operator()(const A& obj) const {
            size_t h1 = hash<int>()(obj.x);
            size_t h2 = hash<float>()(obj.y);
            size_t h3 = hash<char>()(obj.z);
            size_t h4 = hash<string>()(string(obj.a));
            size_t h5 = hash<string>()(obj.b);
            size_t h6 = hash<int>()(obj.c.e);
            size_t h7 = hash<float>()(obj.c.f);

            return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3) ^ (h5 << 4) ^ (h6 << 5) ^ (h7 << 6);
        }
    };

    // template<> 是全特化：template<> 表示全特化，即我们提供了 std::equal_to 对于某个特定类型（A）的特定实现。
    // 全特化是对模板的特定类型的自定义实现，适用于 A 类型。
    // 这个可以不写
    template <>
    struct equal_to<A> {
        bool operator()(const A& lhs, const A& rhs) const {
            return lhs == rhs;
        }
    };
}

int main() {
    // 使用自定义哈希函数和相等比较函数
    unordered_map<A, string, std::hash<A>, std::equal_to<A>> umap;  // 偏特化unordered_map，提供部分特化以适应特定的类型或条件，alloctor没变

    // 插入元素
    A a1(1, 1.5, 'c', "hello", "world", C(10, 2.5));
    umap[a1] = "Example 1";

    A a2(2, 2.5, 'd', "foo", "bar", C(20, 3.5));
    umap[a2] = "Example 2";

    // 查找元素
    cout << umap[a1] << endl;  // 输出：Example 1
    cout << umap[a2] << endl;  // 输出：Example 2

    return 0;
}
