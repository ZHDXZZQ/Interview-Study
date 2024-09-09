# 2024/7/24 MiniMax服务端研发一面
1. 自我介绍
2. 从实习经历中挑一个项目介绍一下，说一些你做的工作、困难和处理策略
3. 容灾的处理是从什么平台去做的？
4. 一些字节的基础问题，比如流量下发，图文和视频的关系等
5. mysql用的多不？隔离级别有什么？
6. 可重复读是通过什么样的机制实现的？
7. MVCC有什么？他是如何解决幻读的
8. 乐观锁和悲观锁的区别
9. abase和redis的区别是啥？
10. redis的数据结构有哪些？
11. 大key或热key如何解决？
12. 手撕：中奖概率：一等奖概率1%，二等奖概率10%，三等奖概率20%，四等奖概率69%，两个一等奖的间隔最大为100人，否则强制中一次，模拟一下，输出第1w人和第2w人中的几等奖。
    ```C++
    #include <iostream>
    #include <vector>
    #include <random>
    #include <string>

    using namespace std;

    int main() {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(1, 100);    // 包括1和100
        int cnt = 99;
        for (int i = 1; i <= 20000; ++ i) {
            int r = dis(gen);
            if (cnt == 0) {
                if (i == 10000 || i == 20000) cout << "people: " << i << " : have 1 ! " << endl;
                cnt = 98;
                continue;
            }
            if (r == 1) {
                if (i == 10000 || i == 20000) cout << "people: " << i << " : have 1 ! " << endl;
                cnt = 99;
            } else if (r >= 2 && r < 12) {
                if (i == 10000 || i == 20000) cout << "people: " << i << " : have 2 ! " << endl;
            } else if (r >= 12 && r < 32) {
                if (i == 10000 || i == 20000) cout << "people: " << i << " : have 3 ! " << endl;
            } else if (r >= 32 && r <= 100) {
                if (i == 10000 || i == 20000) cout << "people: " << i << " : have 4 ! " << endl;
            }
            -- cnt;
        }
        return 0;
    }

    // 利用时间戳做随机数
    #include <iostream>
    #include <chrono>

    using namespace std;
    using namespace std::chrono;

    int main() {
        // 获取当前时间点
        auto now = system_clock::now();
        
        // 直接用这个秒或者毫秒都可以表示随机数
        // 转换为时间戳（秒）
        auto timestamp = system_clock::to_time_t(now);
        
        // 转换为时间戳（毫秒）
        auto timestamp_ms = duration_cast<milliseconds>(now.time_since_epoch()).count();
        
        cout << "当前时间的时间戳（秒）: " << timestamp << endl;
        cout << "当前时间的时间戳（毫秒）: " << timestamp_ms << endl;

        return 0;
    }
    ```
13. 反问：业务是什么？C端到服务端，产品提需响应线上业务，智能体推荐，UGC产品，
14. 反问：技术栈：go、java、C++
15. 反问：需求。公司业务比较多，加班类似字节