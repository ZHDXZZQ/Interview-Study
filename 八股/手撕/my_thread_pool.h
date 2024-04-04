//线程池，最简陋版，其实就是对传入的函数进行并发调用
//我们需要外部传入线程池中的线程需要执行的函数
//获取到需要的线程数量后，批量执行线程即可
//进阶的，可以传入一组函数，依次执行里面的每个函数

#include <thread>
#include <functional>
#include <vector>

class My_Thread_Pool {
public:
    template<typename Return>
    void concurrent_run(int thread_number, std::vector<std::function<Return()>>& func_list) {
        auto func_size = func_list.size();
        if (func_size == 0) { return; }
        int single_func_thread_num = thread_number / func_size;
        for (auto i = 0; i < func_size - 1; ++ i) {
            for (auto j = 0; j <= single_func_thread_num; ++ j) {
                std::thread _thread(func_list[i]);
                thread_q.emplace_back(std::move(_thread));
            }
        }
        int last = thread_number - (func_size - 1) * (single_func_thread_num + 1);
        for (int j = 0; j < last; ++ j) {
            std::thread _thread(func_list[func_size - 1]);
            thread_q.emplace_back(std::move(_thread));
        }
        for (auto& thread : thread_q) {
            thread.join();
        }
    }
private:
    std::vector<std::thread> thread_q;
};