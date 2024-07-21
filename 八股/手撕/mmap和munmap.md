`mmap` 是一种内存映射文件的方法，它允许文件或设备在内存中有一个与之对应的区域。
这种映射提供了文件与内存之间的直接映射，使得对文件内容的访问像对内存操作一样方便。
`mmap` 通常用于提高文件 I/O 的效率，尤其是在处理大型文件或需要频繁访问文件内容的场景中。

### 基本概念

1. **内存映射**：将文件或设备的内容映射到进程的虚拟地址空间。通过这种映射，进程可以像操作内存一样访问文件内容。
2. **共享映射**（shared mapping）和**私有映射**（private mapping）：
   - **共享映射**：对映射区域的修改会直接写入到文件，并且映射该文件的其他进程可以看到这些修改。
   - **私有映射**：对映射区域的修改不会影响文件，修改只对当前进程可见。

### 使用 mmap 的优点

1. **高效的文件 I/O**：避免了显式的读写系统调用，减少了用户态与内核态之间的切换开销。
2. **方便的文件访问**：可以直接对映射区域进行内存操作，代码简洁。
3. **内存共享**：不同进程可以映射同一个文件，从而实现内存共享。

### mmap 系统调用

在 POSIX 系统（如 Linux）中，可以使用 `mmap` 系统调用。以下是 `mmap` 的函数原型：

```c
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
```

- **addr**：指定映射的起始地址，通常设为 `NULL`，让内核选择合适的地址。
- **length**：要映射的字节数。
- **prot**：映射区域的保护标志，如 `PROT_READ`（可读）、`PROT_WRITE`（可写）、`PROT_EXEC`（可执行）。
- **flags**：映射的类型和属性，如 `MAP_SHARED`（共享映射）、`MAP_PRIVATE`（私有映射）。
- **fd**：要映射文件的文件描述符。
- **offset**：文件映射的起始偏移量，通常为 0。

返回值是指向映射区域的指针，如果失败则返回 `MAP_FAILED`。

### 示例代码

以下是一个使用 `mmap` 读取文件内容的示例：

```cpp
#include <iostream>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    const char* filePath = "example.txt";
    /*
        open：系统调用，用于打开文件并返回文件描述符。
        int open(const char *pathname, int flags);
        pathname：要打开的文件路径。flags：打开文件的模式（如只读、读写等）。
        成功时返回文件描述符。失败时返回 -1，并设置 errno 来指示错误。
    */
    int fd = open(filePath, O_RDONLY);  // 文件路径和读写模式
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }
    // perror 是一个标准库函数，用于输出错误信息。
    // void perror(const char *s);
    // s：要输出的错误前缀字符串。

    // fstat 是一个系统调用，用于获取打开文件的状态信息，并将这些信息存储在 stat 结构体中。
    // int fstat(int fd, struct stat *buf);
    // fd：文件描述符。buf：指向存储文件状态信息的 stat 结构体的指针。
    // 成功时返回 0。失败时返回 -1，并设置 errno 来指示错误。
    struct stat fileStat;   // 包含文件各种信息
    // struct stat {
    //     dev_t     st_dev;     // ID of device containing file
    //     ino_t     st_ino;     // Inode number
    //     mode_t    st_mode;    // File type and mode
    //     nlink_t   st_nlink;   // Number of hard links
    //     uid_t     st_uid;     // User ID of owner
    //     gid_t     st_gid;     // Group ID of owner
    //     dev_t     st_rdev;    // Device ID (if special file)
    //     off_t     st_size;    // Total size, in bytes
    //     blksize_t st_blksize; // Block size for filesystem I/O
    //     blkcnt_t  st_blocks;  // Number of 512B blocks allocated
    //     time_t    st_atime;   // Time of last access
    //     time_t    st_mtime;   // Time of last modification
    //     time_t    st_ctime;   // Time of last status change
    // };
    if (fstat(fd, &fileStat) == -1) {   // 获取文件状态
        perror("Error getting file size");
        close(fd);
        return 1;
    }

    size_t fileSize = fileStat.st_size;
    void* mapped = mmap(NULL, fileSize, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mapped == MAP_FAILED) {
        perror("Error mapping file");
        close(fd);
        return 1;
    }

    // 输出文件内容
    std::cout.write(static_cast<char*>(mapped), fileSize);
    // std::ostream& write(const char* s, std::streamsize n);
    // s：指向要写入的字符数组的指针。n：要写入的字符数。
    // std::cout.write 是 C++ 标准库中的一个成员函数，用于将字符数组的内容写入到输出流。它的常见用法是直接输出一个指定长度的字符数组。


    // 解除映射系统调用
    // int munmap(void *addr, size_t length);
    // addr：指向要解除映射的内存地址。 length：要解除映射的字节数。
    // 成功时返回 0。失败时返回 -1，并设置 errno 来指示错误。
    if (munmap(mapped, fileSize) == -1) {
        perror("Error unmapping file");
    }

    close(fd);
    // close 是一个系统调用，用于关闭文件描述符。
    // int close(int fd);
    // fd：要关闭的文件描述符。
    // 成功时返回 0。失败时返回 -1，并设置 errno 来指示错误。
    return 0;
}
```

### 总结

- `mmap` 是一种强大的文件 I/O 技术，它允许将文件内容映射到进程的虚拟地址空间，从而使文件操作像内存操作一样高效。
- `mmap` 支持共享映射和私有映射，适用于不同的场景需求。
- 通过 `mmap` 可以减少系统调用的开销，提高文件访问的性能，特别是对于大文件或频繁访问文件内容的应用程序。
