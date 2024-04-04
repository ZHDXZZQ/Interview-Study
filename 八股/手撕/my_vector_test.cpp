//简易单元测试

#include "my_vector.h"

int main() {
    MyVector<int> myvec;
    myvec.push_back(2);
    std::cout << myvec[2] << std::endl;
    return 0;
}