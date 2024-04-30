// 本文利用两个无名管道实现，读会阻塞，类似于信号量，适用于父子进程
// 后续可以做一下有名管道的实现
// 有名管道：int mkfifo(const char *pathname, mode_t mode);
#include <iostream>
#include <unistd.h>

int main() {
    int pipefd[2];       // 0读1写
    int pipefd2[2];      // 0读1写
    if (pipe(pipefd) == -1) {
        // int pipe(int pipefd[2]); 成功返回0，失败返回-1
        perror("创建无名管道失败");
        // 将error信息打印到传入的string后到终端
        return 1;
    }
    if (pipe(pipefd2) == -1) {
        perror("创建无名管道2失败");
        return 1;
    }

    pid_t pid = fork();
    // pid_t fork(void);
    // 创建一个新进程，新进程称为子进程，原进程称为父进程，两个进程几乎完全相同（除了返回值和进程ID不同），并行执行。
    // 在父进程中，返回子进程的id；子进程中返回0，失败返回-1
    // std::cout << pid << std::endl;
    if (pid == -1) {
        perror("创建子进程失败");
        return 1;
    }

    // ssize_t read(int fd, void *buf, size_t count);  write函数同理
    // fd是文件描述符；buf是用于存放读取数据的缓冲区；count是要读取的字节数。
    // 成功返回实际读取的字节数，如果已经到达文件尾部则返回0，失败返回-1。
    // 默认情况下，read() 函数是阻塞的，即如果没有数据可读，则调用 read() 会阻塞当前进程，直到有数据可读为止。
    // 要使 read() 函数非阻塞，可以使用 fcntl() 函数设置文件描述符的 O_NONBLOCK 标志。
    // #include <fcntl.h>
    // int fcntl(int fd, int cmd, ... /* arg */ );
    // int flags = fcntl(fd, F_GETFL);
    // fcntl(fd, F_SETFL, flags | O_NONBLOCK);
    // F_GETFL：获取文件描述符的状态标志。
    // F_SETFL：设置文件描述符的状态标志。

    if (pid == 0) { // 子进程
        int num = 0;
        while (num <= 99) {
            read(pipefd2[0], &num, sizeof(num)); // 读取管道中的数据，读不到则阻塞等待
            printf("Child:  %d\n", num);
            ++ num;
            write(pipefd[1], &num, sizeof(num)); // 写入管道，交给父进程
        }
    } else { // 父进程
        int num = 0;
        while (num <= 100) {
            if (num != 0) {
                read(pipefd[0], &num, sizeof(num)); // 读取管道中的数据，读不到则阻塞等待
            }
            printf("Parent: %d\n", num);
            ++ num;
            write(pipefd2[1], &num, sizeof(num)); // 写入管道，交给子进程
        }
    }
    close(pipefd[0]);   //关闭读端
    close(pipefd[1]);   //关闭写端
    close(pipefd2[0]);   //关闭读端
    close(pipefd2[1]);   //关闭写端
    // int close(int fd); 关闭文件描述符，成功返回0，失败返回-1

    return 0;
}
