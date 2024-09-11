// cc、c、cpp、h、hh、hpp文件扩展名功能都类似
// 更高级的，我们可以实现一个可以根据实际情况动态扩充的线程池
#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <stdexcept>

using namespace std;

class ThreadPool {
private:
    using Task = function<void()>;
    vector<thread> threads;
    queue<Task> tasks;
    mutex lockQueue;
    condition_variable cv;
    atomic<bool> run {true};

public:
    ThreadPool(int size = 4): threads(size) {
        for (int i = 0; i < size; ++i) {
            threads[i] = thread([this] {
                while (true) {
                    Task task;
                    {
                        unique_lock<mutex> lock(lockQueue); // 确保了接下来的操作（等待和任务提取）是线程安全的，防止数据竞争。
                        cv.wait(lock, [this] { return !run || !tasks.empty(); });   // 只要结果为true则不阻塞，锁依然持有
                        // 阻塞当前线程，直到满足条件：run 为 false（线程池关闭），或者任务队列非空（有任务可执行）。
                        // 当条件为真时，解除阻塞并继续执行代码。

                        if (!run && tasks.empty())  // 如果线程池已经停止且任务队列为空，线程退出循环并结束。
                            return;
                        // 如果线程池已停止并且没有剩余任务，则该线程退出循环，结束执行。
                        // 这条语句是安全退出线程的关键，防止线程在停止后仍然运行。
                        // 如果队列不空则要执行完

                        task = move(tasks.front()); // 获取一个任务，通过右值引用避免拷贝
                        tasks.pop();
                    }
                    task(); // 执行任务
                }
            });
        }
    }

    ~ThreadPool() {
        {
            unique_lock<mutex> lock(lockQueue);
            run = false;    // 置false停止线程执行新的任务
        }
        cv.notify_all();    // 唤醒所有线程
        // cv.notify_all(); 通过条件变量 cv 唤醒所有在 cv.wait() 处等待的线程。
        // 这些线程在被唤醒后会检查 run 的状态：
        // 如果 run 是 false 并且任务队列为空，它们将会安全退出。
        // 唤醒的目的是为了让线程及时响应线程池的关闭操作，避免陷入无休止的等待。
        for (auto& thread : threads) {
            if (thread.joinable())  //  检查线程是否可以被 join（即线程尚未被 join 或 detach）。
                thread.join();  // 等待每个线程执行完并退出
        }
    }

public:
    template<class F, class... Args>
    auto submit(F&& f, Args&&... args) -> future<decltype(f(args...))> {    // f是提交的函数，args是参数包
        if (!run)   // 如果停止执行了
            throw runtime_error("ThreadPool is stopped");

        using RetType = decltype(f(args...));   // 推断函数f的返回类型
        auto task = make_shared<packaged_task<RetType()>>(bind(forward<F>(f), forward<Args>(args)...));
        // packaged_task 是 C++ 标准库提供的一个模板类，用于封装一个可调用对象，并将其与 future 关联，以便获取其返回值或异常。
        // bind(forward<F>(f), forward<Args>(args)...) 将任务 f 和它的参数包 args 绑定到一个新的任务对象中。
        // forward<F>(f) 和 forward<Args>(args)... 完美转发函数对象和参数，保留它们的值类别（左值或右值）。

        future<RetType> future = task->get_future();
        // 调用 task->get_future() 创建一个 future 对象，该对象与 packaged_task 关联，用于在任务完成时获取其结果。
        {
            lock_guard<mutex> lock(lockQueue);
            tasks.emplace([task]() { (*task)(); }); // 插入任务队列
        }
        cv.notify_one();    // 唤醒一个线程干活
        return future;  // 返回之前创建的 future 对象，以便调用者可以用它来获取任务的执行结果。
    }

    int threadCount() const {
        return threads.size();
    }

    int taskCount() const {
        lock_guard<mutex> lock(lockQueue);
        return tasks.size();
    }
};

// Example usage:
int main() {
    ThreadPool pool(4);

    auto task1 = pool.submit([] {
        cout << "Task 1 executed" << endl;
        return 1;
    });

    auto task2 = pool.submit([] {
        cout << "Task 2 executed" << endl;
        return 2.0;
    });

    try {
        auto task3 = pool.submit([] {
            throw runtime_error("Exception in task 3");
            return 'c';
        });
    } catch (const exception& e) {
        cout << "Exception in task 3: " << e.what() << endl;
    }

    this_thread::sleep_for(chrono::seconds(1));

    cout << "Number of threads in pool: " << pool.threadCount() << endl;
    cout << "Number of tasks in queue: " << pool.taskCount() << endl;

    return 0;
}


// 函数示例
// 示例函数
void printMessage(const string& message) {
    cout << "Message: " << message << endl;
}

// 示例函数，返回一个整数
int computeSum(int a, int b) {
    return a + b;
}

// 示例函数，返回一个浮点数
double computeAverage(double a, double b, double c) {
    return (a + b + c) / 3.0;
}

int main() {
    try {
        // 创建一个线程池，默认大小为 4
        ThreadPool pool;

        // 提交打印消息的任务
        auto future1 = pool.submit([] {
            printMessage("Hello from thread pool!");
        });

        // 提交计算和返回整数的任务
        auto future2 = pool.submit(computeSum, 5, 7);

        // 提交计算和返回浮点数的任务
        auto future3 = pool.submit(computeAverage, 1.0, 2.0, 3.0);

        // 获取和打印任务结果
        cout << "Sum: " << future2.get() << endl;  // 输出：Sum: 12
        cout << "Average: " << future3.get() << endl;  // 输出：Average: 2.0

        // 故意抛出异常的任务
        auto future4 = pool.submit([] {
            throw runtime_error("Exception from task");
        });

        // 捕获异常
        try {
            future4.get();
        } catch (const runtime_error& e) {
            cout << "Caught exception: " << e.what() << endl;
        }

        // 检查线程池状态
        cout << "Number of threads in pool: " << pool.threadCount() << endl;
        cout << "Number of tasks in queue: " << pool.taskCount() << endl;

    } catch (const exception& e) {
        cout << "Caught exception: " << e.what() << endl;
    }

    return 0;
}