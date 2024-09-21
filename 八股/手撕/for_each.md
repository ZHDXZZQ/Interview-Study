`std::for_each` 是 C++ 标准库中用于遍历容器元素并对每个元素执行指定操作的算法。它属于 `<algorithm>` 头文件中的标准算法之一，适用于数组、`std::vector`、`std::list` 等 STL 容器或任何其他迭代器范围。

### 函数原型

```cpp
template<class InputIt, class UnaryFunction>
UnaryFunction for_each(InputIt first, InputIt last, UnaryFunction f);
```

#### 参数说明：
- **`InputIt first`**：指向容器或范围的起始迭代器。
- **`InputIt last`**：指向容器或范围的结束迭代器，遍历会执行到（但不包括）`last`。
- **`UnaryFunction f`**：一个接受单一参数的可调用对象（例如函数、函数对象、lambda 表达式），对每个元素进行操作。

#### 返回值：
- 返回传入的函数对象 `f`（也就是 `UnaryFunction`），所以可以用于一些带状态的函数对象。

### 基本用法示例

#### 1. 使用普通函数

```cpp
#include <iostream>
#include <vector>
#include <algorithm> // for_each

void printElement(int x) {
    std::cout << x << " ";
}

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // 使用 for_each 遍历 vec 并调用 printElement 函数
    std::for_each(vec.begin(), vec.end(), printElement);

    return 0;
}
```

**输出**：
```
1 2 3 4 5
```

#### 2. 使用 Lambda 表达式

```cpp
#include <iostream>
#include <vector>
#include <algorithm> // for_each

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // 使用 lambda 表达式来打印每个元素
    std::for_each(vec.begin(), vec.end(), [](int x) {
        std::cout << x << " ";
    });

    return 0;
}
```

**输出**：
```
1 2 3 4 5
```

#### 3. 修改容器中的元素

`std::for_each` 也可以修改容器中的元素，前提是通过引用传递元素。

```cpp
#include <iostream>
#include <vector>
#include <algorithm> // for_each

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // 使用 lambda 表达式修改每个元素的值
    std::for_each(vec.begin(), vec.end(), [](int& x) {
        x *= 2;  // 将每个元素都乘以 2
    });

    // 打印修改后的容器
    std::for_each(vec.begin(), vec.end(), [](int x) {
        std::cout << x << " ";
    });

    return 0;
}
```

**输出**：
```
2 4 6 8 10
```

#### 4. 使用函数对象

```cpp
#include <iostream>
#include <vector>
#include <algorithm> // for_each

struct MultiplyBy {
    int factor;
    MultiplyBy(int f) : factor(f) {}
    void operator()(int& x) const {
        x *= factor;
    }
};

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // 使用函数对象 MultiplyBy 来修改容器元素
    std::for_each(vec.begin(), vec.end(), MultiplyBy(3));  // 将每个元素乘以 3

    // 打印结果
    std::for_each(vec.begin(), vec.end(), [](int x) {
        std::cout << x << " ";
    });

    return 0;
}
```

**输出**：
```
3 6 9 12 15
```

### 适用场景

1. **遍历容器并执行操作**：最常见的场景是遍历一个容器并对每个元素执行某种操作（如打印、修改等），尤其是在需要更优雅的方式处理循环时。
   
2. **函数对象应用**：如果需要将容器元素传递给某个复杂的操作，使用函数对象可以灵活传递状态或参数。

3. **修改容器中的元素**：通过传递引用，可以使用 `std::for_each` 对容器中的元素进行就地修改。

4. **函数链调用或状态累积**：由于 `std::for_each` 返回的是其操作对象，函数对象或 lambda 表达式可以累积状态，从而实现复杂操作。

### 总结

`std::for_each` 是一个非常有用的工具，它可以用于遍历容器并对每个元素执行指定的操作。在现代 C++ 中，尤其是与 lambda 表达式结合使用时，`for_each` 提供了非常简洁的代码风格。