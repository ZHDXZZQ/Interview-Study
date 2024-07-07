### `memset`
`memset` 函数用于将内存块的某一特定值设置为指定的值。

```cpp
#include <iostream>
#include <cstring> // 包含memset

int main() {
    char arr[10];

    // 将数组的所有元素设置为 'A'，不适用于设置非字符数组或非字节数组的值。
    // 对于 int 类型数组，建议使用 std::fill 或手动循环来初始化值： std::fill(arr, arr + 10, 5);
    // void std::fill(ForwardIterator first, ForwardIterator last, const T& value);
    // first为范围起始的迭代器，last为结尾的迭代器（不包含），这里同样适用于vec的begin和end，value为要填充的值

    // void* memset(void* ptr, int value, size_t num); 返回指向目标内存块的指针
    // ptr指向要填充的内存块，value表示要设置的值，num表示要设置的字节数，是按字节赋值的，所以对于非字节的变量要注意
    // 性能：memset 通常用于初始化较大的内存块，它在性能上非常高效。
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
    // void* memcpy(void* destination, const void* source, size_t num);
    // dest指向目标内存块，src指向源内存块，num表示要赋值的字节数，返回指向目标内存块的指针，按字节赋值，不检查边界情况
    // memcpy 通常在实现上非常高效，因为它是一个低级别的内存操作函数。
    // 如果内存区域重叠，请使用 memmove，它保证正确处理重叠区域。
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
    // void *memmove(void *dest, const void *src, size_t n);
    // dest指向目标内存的指针，srd指向源内存的指针，n为要移动的内存数
    // 即便两个区域有内存重叠，也会完美移动，比memcpy更好
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
    // int memcmp(const void *s1, const void *s2, size_t n);
    // s1指向第一个内存块，s2指向第二个内存块，n为两边要比较的字节数，不从0开始
    // 返回0表示相等，小于0表示不同的第一个字节中的值s1小于s2，大于0表示s1大于s2
    // 如果比较的字符数多余了字符串的长度，则短的那个最后一个用'\0'（ascii为0）来和对应位置的字符比较并返回结果
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
    // void *memchr(const void *s, int c, size_t n);
    // s表示被搜索的内存，c表示要查找的字符，n表示要搜索的字节数
    // 返回值为找到的字符的指针
    // 传递给 memchr 的字符 c 会被转换为 unsigned char，确保正确处理非 ASCII 字符。
    // memchr 可以用于查找任意内存块中的字符，而不仅仅是字符串数据。
    char* result = (char*)memchr(str, ch, sizeof(str));

    if (result != nullptr) {
        std::cout << "memchr: Found '" << ch << "' at position: " << (result - str) << std::endl;
    } else {
        std::cout << "memchr: Character '" << ch << "' not found" << std::endl;
    }

    return 0;
}
```