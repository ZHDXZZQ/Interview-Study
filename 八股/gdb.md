# GDB相关命令，用于调试及排查CoreDump
    
> g++ -g test.cpp -o test，添加-g参数，保留info   
> ulimit -c unlimited 不限制core dump文件大小，执行以保证生成core文件  
       
1. gdb：解释coredump文件
    - gdb xx.elf xx.core
    - gdb core.xx
    - gdb xx_program core.yy
2. bt：backtrace，显示堆栈
3. f：frame，调用查看指定的栈帧
    - frame x
    - f x
4. p：print，打印变量名的值
    - print variable
    - p x
5. i：info，i打印对应信息
    - info locals       // 查看当前帧局部变量及值
    - info args         // 查看当前函数的参数
    - info registers    // 查看寄存器
6. list：查看执行点附近的源代码
    - list x     // 指定行附近的源代码
7. disassemble：查看当前函数汇编代码
8. up：切换到上一帧（调用者函数）
9. down：切换到下一帧（被调函数）
10. q：quit，退出gdb
11. t：thread，管理和查看线程
    - thread apply [thread id] [command]: 对指定线程执行一个命令。
    - thread apply all [command]: 对所有线程执行一个命令。
    - thread [thread id]: 切换到指定的线程。
    - 例如：thread apply all bt
12. b：breakpoint：在指定位置设置断点
    - b filename:line_number    // 在指定行设置断点
    - b function_name           // 在指定函数设置断点
13. c：coutinue，继续执行程序，直到遇到下一个断点
14. n：next，单步执行下一行代码，如果当前行是一个函数调用，则调用该函数
15. step：单步执行下一行代码，如果当前行是一个函数，则执行函数第一行
16. r：run，启动程序，如果程序已经在运行，可以使用kill停止，然后再次使用run命令启动