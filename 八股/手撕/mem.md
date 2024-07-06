下面是展示几种常用的内存操作函数（如 `memset` 和 `memcpy`）的 C++ 示例代码。

### `memset`
`memset` 函数用于将内存块的某一特定值设置为指定的值。

```cpp
#include <iostream>
#include <cstring> // 包含memset

int main() {
    char arr[10];

    // 将数组的所有元素设置为 'A'，不适用于设置非字符数组或非字节数组的值。
    // 对于 int 类型数组，建议使用 std::fill 或手动循环来初始化值： std::fill(arr, arr + 10, 5);
    memset(arr, 'A', sizeof(arr));

    // 输出数组的内容
    std::cout << "memset: ";
    for (char c : arr) {
        std::cout << c << ' ';
    }
    std::cout << std::endl;

    return 0;
}
```

### `memcpy`
`memcpy` 函数用于将源内存块中的数据复制到目标内存块中。注意，`memcpy` 不处理重叠的内存区域，如果需要处理重叠区域，应该使用 `memmove`。

```cpp
#include <iostream>
#include <cstring> // 包含memcpy

int main() {
    char src[] = "Hello, World!";
    char dest[20];

    // 将src数组的内容复制到dest数组
    memcpy(dest, src, sizeof(src));

    // 输出dest数组的内容
    std::cout << "memcpy: " << dest << std::endl;

    return 0;
}
```

### `memmove`
`memmove` 函数用于将源内存块中的数据复制到目标内存块中。`memmove` 能够处理重叠的内存区域。

```cpp
#include <iostream>
#include <cstring> // 包含memmove

int main() {
    char str[] = "Hello, World!";

    // 重叠区域的移动
    memmove(str + 7, str, 5);

    // 输出字符串的内容
    std::cout << "memmove: " << str << std::endl;

    return 0;
}
```

### `memcmp`
`memcmp` 函数用于比较两个内存块的内容。

```cpp
#include <iostream>
#include <cstring> // 包含memcmp

int main() {
    char str1[] = "Hello";
    char str2[] = "Hello";
    char str3[] = "World";

    // 比较str1和str2
    int result1 = memcmp(str1, str2, sizeof(str1));
    std::cout << "memcmp (str1 vs str2): " << result1 << std::endl;

    // 比较str1和str3
    int result2 = memcmp(str1, str3, sizeof(str1));
    std::cout << "memcmp (str1 vs str3): " << result2 << std::endl;

    return 0;
}
```

### `memchr`
`memchr` 函数用于在内存块中查找第一次出现的指定字符。

```cpp
#include <iostream>
#include <cstring> // 包含memchr

int main() {
    char str[] = "Hello, World!";
    char ch = 'W';

    // 在str数组中查找字符 'W'
    char* result = (char*)memchr(str, ch, sizeof(str));

    if (result != nullptr) {
        std::cout << "memchr: Found '" << ch << "' at position: " << (result - str) << std::endl;
    } else {
        std::cout << "memchr: Character '" << ch << "' not found" << std::endl;
    }

    return 0;
}
```