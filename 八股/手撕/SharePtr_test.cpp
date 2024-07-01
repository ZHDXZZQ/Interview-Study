#include <iostream>
#include "my_shared_ptr.h"

// 示例
int main() {
    SharedPtr<int> sp1(new int(10)); // 创建一个 SharedPtr 对象，指向整数 10
    std::cout << "sp1 use count: " << sp1.use_count() << std::endl; // 输出引用计数

    {
        SharedPtr<int> sp2 = sp1; // 拷贝构造，sp2 和 sp1 指向同一对象
        std::cout << "sp1 use count: " << sp1.use_count() << std::endl; // 输出引用计数
        std::cout << "sp2 use count: " << sp2.use_count() << std::endl; // 输出引用计数
    } // sp2 离开作用域，引用计数减1

    std::cout << "sp1 use count: " << sp1.use_count() << std::endl; // 输出引用计数

    return 0;
}