`std::string_view` 是 C++17 引入的一个轻量级非拥有（non-owning）字符串视图。它提供了一种查看和操作字符串数据的方式，而不需要进行复制。
`std::string_view` 可以用来避免不必要的内存分配和数据拷贝，从而提高性能。它适用于只读操作，不会修改原始字符串。

### 应用场景

1. **性能优化**：
   - 避免字符串的拷贝操作，减少内存分配和释放的开销。
   - 当函数只需要读取字符串数据时，可以使用 `std::string_view` 作为参数类型，而不是 `std::string`。

2. **处理子字符串**：
   - 快速创建字符串的子视图，而不需要进行实际的字符串拷贝。
   - 提供灵活的字符串操作，例如分割、查找子串等。

3. **与旧代码兼容**：
   - 方便地与 C 风格字符串（`const char*`）和 `std::string` 互操作。

### 实际代码示例

下面是一些使用 `std::string_view` 的实际代码示例：

#### 1. 函数参数优化，类似引用，但可避免引用导致的悬挂引用（指空，内存泄露），只读不修改原串，避免拷贝

```cpp
#include <iostream>
#include <string>
#include <string_view>

void print_view(std::string_view sv) {
    std::cout << sv << '\n';
}

int main() {
    std::string str = "Hello, World!";
    print_view(str); // 从 std::string 创建 string_view
    print_view("Hello, C++17!"); // 从字符串字面值创建 string_view
    return 0;
}
```

#### 2. 创建子视图，而不必要对子串创建一个新的string对象，避免拷贝

```cpp
#include <iostream>
#include <string>
#include <string_view>

int main() {
    std::string str = "Hello, World!";
    std::string_view sv = str;

    std::string_view sv1 = sv.substr(0, 5); // "Hello"
    std::string_view sv2 = sv.substr(7);    // "World!"

    std::cout << sv1 << '\n';
    std::cout << sv2 << '\n';

    return 0;
}
```

#### 3. 避免不必要的拷贝，允许函数接收多种字符串类型，接口统一，不需要重载

```cpp
#include <iostream>
#include <string>
#include <string_view>

void find_and_print(std::string_view sv, char c) {  // 虽然没有使用引用，但是不拷贝
    size_t pos = sv.find(c);
    if (pos != std::string_view::npos) {
        std::cout << "Found '" << c << "' at position " << pos << '\n';
    } else {
        std::cout << "Character '" << c << "' not found\n";
    }
}

int main() {
    std::string str = "Hello, World!";
    find_and_print(str, 'W');
    find_and_print("Hello, C++17!", '+');
    return 0;
}
```

#### 4. 与 C 风格字符串兼容，比直接传引用的方法更灵活兼容

```cpp
#include <iostream>
#include <string_view>

void print_cstring_view(const char* cstr) {
    std::string_view sv(cstr);
    std::cout << sv << '\n';
}

int main() {
    const char* cstr = "Hello, C-String!";
    print_cstring_view(cstr);
    return 0;
}
```

### 注意事项

1. **生命周期管理**：
   - `std::string_view` 不负责管理底层数据的生命周期。确保在使用 `std::string_view` 时，底层数据的生命周期是有效的。

2. **只读操作**：
   - `std::string_view` 仅支持只读操作，不能用于修改底层字符串数据。

3. **不支持空终止符**：
   - `std::string_view` 不保证底层数据以空终止符结尾，因此在与 C 风格字符串交互时需要小心。即string view的结尾不是'\0'

使用 `std::string_view` 可以显著提高字符串处理的效率，特别是在需要只读访问和避免不必要的拷贝时。