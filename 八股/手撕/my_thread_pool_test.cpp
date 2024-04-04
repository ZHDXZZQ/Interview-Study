//自制线程池的简单单测

# include "my_thread_pool.h"
# include <iostream>

void print(int i) {
    std::cout << i << " test! " << std::endl;
}

int main() {
    std::vector<std::function<void()>> funcs;
    for (int i = 0; i < 3; ++ i) {
        funcs.emplace_back([i]() { 
            print(i);
        });
    }
    
    auto my_thread_pool = new My_Thread_Pool();
    my_thread_pool->concurrent_run(5, funcs);
    return 0;
}