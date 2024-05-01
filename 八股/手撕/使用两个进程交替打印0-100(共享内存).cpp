// 共享内存，适用于父子进程和非父子进程
// 同理可以使用文件来进行信息交换
// 编译最后加 -lrt
// 编译命令 g++ 使用两个进程交替打印0-100\(共享内存\).cpp -o test -lrt
#include <iostream>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define SHARED_MEMORY_NAME "/my_shared_memory"  //定义共享内存文件名

int main() {
    int shm_fd = shm_open(SHARED_MEMORY_NAME, O_CREAT | O_RDWR, 0666);
    // int shm_open(const char *name, int oflag, mode_t mode);
    // name为IPC的名字，格式为/xxx
    // oflag为标志，有O_CREAT：未创建则创建；O_RDWR：读写；O_RDONLY：只读
    // mode为权限，有S_IXYYY：X为W/R即写/读，YYY为对象如USR/GPR/OTH，即用户主/群组成员/其他成员
    // 返回-1为失败，其他则为返回的文件描述符
    if (shm_fd == -1) {
        perror("共享内存创建/打开失败");
        exit(EXIT_FAILURE);
    }

    if (ftruncate(shm_fd, sizeof(int)) == -1) {
        // int ftruncate(int fd, off_t length);
        // 调整文件大小，成功返回0，失败为-1
        perror("调整共享内存对象大小失败");
        exit(EXIT_FAILURE);
    }

    void* ptr = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    // void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
    // 将文件或共享内存映射到进程的地址空间
    // addr：映射的起始地址，通常为 NULL，由系统选择合适的地址。
    // length：映射的大小。单位字节，不足一页按一页处理。
    // prot：映射区域的保护模式，例如 PROT_READ 表示可读，PROT_WRITE 表示可写。
    // flags：映射选项，例如 MAP_SHARED 表示映射共享，MAP_PRIVATE 表示映射私有。
    // fd：文件描述符，用于指定需要映射的文件或共享内存。
    // offset：文件中的偏移量，通常为 0。
    // 返回值：成功返回映射区域的起始地址，失败返回 MAP_FAILED。
    if (ptr == MAP_FAILED) {
        perror("内存映射失败");
        exit(EXIT_FAILURE);
    }

    int* shared_data = static_cast<int*>(ptr);  //类型转换
    *shared_data = 0;

    pid_t pid = fork();
    if (pid == -1) {
        perror("子进程创建失败");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        while (*shared_data <= 99) {
            if (*shared_data % 2 == 1) {
                std::cout << "Child  Process: shared_data = " << *shared_data << std::endl;
                ++ *shared_data;
            }
        }
        exit(EXIT_SUCCESS); //退出该进程，并返回退出值
        // void exit(int status); 
        // status表示进程的退出状态，通常情况下，0 表示成功，其他值表示失败。
    } else {
        while (*shared_data <= 100) {
            if (*shared_data % 2 == 0) {    //加限制条件，让两个进程交替执行
                std::cout << "Parent Process: shared_data = " << *shared_data << std::endl;
                ++ *shared_data;
            }
        }
        wait(nullptr);
        // pid_t wait(int *status);
        // 其中，status 参数是一个指向整数的指针，用于存储子进程的退出状态。
        // 如果调用 wait() 函数时没有子进程退出，父进程会被阻塞，直到有一个子进程退出。
        // 如果父进程不关心子进程的退出状态，可以将 status 参数设置为 NULL。
    }
    if (munmap(ptr, sizeof(int)) == -1) {
        // int munmap(void *addr, size_t length);
        // 取消映射，成功返回 0，失败返回 -1。
        // addr：映射区域的起始地址。
        // length：映射的大小。
        perror("释放内存映射失败");
        exit(EXIT_FAILURE);
    }
    if (shm_unlink(SHARED_MEMORY_NAME) == -1) {
        // int shm_unlink(const char *name);
        // 删除共享内存对象，成功返回0，失败返回-1
        perror("释放共享内存失败");
        exit(EXIT_FAILURE);
    }
    return 0;
}
