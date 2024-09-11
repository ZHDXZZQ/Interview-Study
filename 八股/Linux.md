# 本文介绍Linux系统的常用命令

> 具体的用时再搜再补，gpt很强大   

1. ls：查看当前目录所有子文件
    ```
    ls -l    列列出详细信息
    ls -a    查看所有文件包括隐藏文件
    ls -h    内存空间显示单位
    ls -R    查看所有子目录的所有文件
    ```
2. cd xxx：进入xxx目录
3. rm -rf xxx：删除xxx文件或目录
4. cp xxx yyy：复制xxx到yyy
5. mv xxx yyy：移动xxx到yyy，同改名
6. cat xxx：查看xxx
7. ctrl + c：取消命令并换行
8. tab：按一次补全，按两次展示备选
9. mkdir xxx：创建xxx目录
10. pwd：展示当前路径
11. md5sum xxx：计算文件哈希值
12. ag xxx：搜索当前目录下所有文件，检索xxx字符串
13. touch xxx：创建一个文件
14. tmux：分屏，允许断开Terminal连接后，继续运行进程。
    ```
    Ref：AcWing
    结构：
        一个tmux可以包含多个session，一个session可以包含多个window，一个window可以包含多个pane。
        实例：
            tmux:
                session 0:
                    window 0:
                        pane 0
                        pane 1
                        pane 2
                        ...
                    window 1
                    window 2
                    ...
                session 1
                session 2
                ...
    操作：
        (1) tmux：新建一个session，其中包含一个window，window中包含一个pane，pane里打开了一个shell对话框。
        (2) 按下Ctrl + a后手指松开，然后按%：将当前pane左右平分成两个pane。
        (3) 按下Ctrl + a后手指松开，然后按"（注意是双引号"）：将当前pane上下平分成两个pane。
        (4) Ctrl + d：关闭当前pane；如果当前window的所有pane均已关闭，则自动关闭window；如果当前session的所有window均已关闭，则自动关闭session。
        (5) 鼠标点击可以选pane。
        (6) 按下ctrl + a后手指松开，然后按方向键：选择相邻的pane。
        (7) 鼠标拖动pane之间的分割线，可以调整分割线的位置。
        (8) 按住ctrl + a的同时按方向键，可以调整pane之间分割线的位置。
        (9) 按下ctrl + a后手指松开，然后按z：将当前pane全屏/取消全屏。
        (10) 按下ctrl + a后手指松开，然后按d：挂起当前session。
        (11) tmux a：打开之前挂起的session。
        (12) 按下ctrl + a后手指松开，然后按s：选择其它session。
            方向键 —— 上：选择上一项 session/window/pane
            方向键 —— 下：选择下一项 session/window/pane
            方向键 —— 右：展开当前项 session/window
            方向键 —— 左：闭合当前项 session/window
        (13) 按下Ctrl + a后手指松开，然后按c：在当前session中创建一个新的window。
        (14) 按下Ctrl + a后手指松开，然后按w：选择其他window，操作方法与(12)完全相同。
        (15) 按下Ctrl + a后手指松开，然后按PageUp：翻阅当前pane内的内容。
        (16) 鼠标滚轮：翻阅当前pane内的内容。
        (17) 在tmux中选中文本时，需要按住shift键。（仅支持Windows和Linux，不支持Mac，不过该操作并不是必须的，因此影响不大）
        (18) tmux中复制/粘贴文本的通用方式：
            (1) 按下Ctrl + a后松开手指，然后按[
            (2) 用鼠标选中文本，被选中的文本会被自动复制到tmux的剪贴板
            (3) 按下Ctrl + a后松开手指，然后按]，会将剪贴板中的内容粘贴到光标处
    ```
15. vim：i esc wq q!
    ```
    Ref：AcWing
    功能：
        (1) 命令行模式下的文本编辑器。
        (2) 根据文件扩展名自动判别编程语言。支持代码缩进、代码高亮等功能。
        (3) 使用方式：vim filename
            如果已有该文件，则打开它。
            如果没有该文件，则打开个一个新的文件，并命名为filename
    模式：
        (1) 一般命令模式
            默认模式。命令输入方式：类似于打游戏放技能，按不同字符，即可进行不同操作。可以复制、粘贴、删除文本等。
        (2) 编辑模式
            在一般命令模式里按下i，会进入编辑模式。
            按下ESC会退出编辑模式，返回到一般命令模式。
        (3) 命令行模式
            在一般命令模式里按下:/?三个字母中的任意一个，会进入命令行模式。命令行在最下面。
            可以查找、替换、保存、退出、配置编辑器等。
    操作：
        (1) i：进入编辑模式
        (2) ESC：进入一般命令模式
        (3) h 或 左箭头键：光标向左移动一个字符
        (4) j 或 向下箭头：光标向下移动一个字符
        (5) k 或 向上箭头：光标向上移动一个字符
        (6) l 或 向右箭头：光标向右移动一个字符
        (7) n<Space>：n表示数字，按下数字后再按空格，光标会向右移动这一行的n个字符
        (8) 0 或 功能键[Home]：光标移动到本行开头
        (9) $ 或 功能键[End]：光标移动到本行末尾
        (10) G：光标移动到最后一行
        (11) :n 或 nG：n为数字，光标移动到第n行
        (12) gg：光标移动到第一行，相当于1G
        (13) n<Enter>：n为数字，光标向下移动n行
        (14) /word：向光标之下寻找第一个值为word的字符串。
        (15) ?word：向光标之上寻找第一个值为word的字符串。
        (16) n：重复前一个查找操作
        (17) N：反向重复前一个查找操作
        (18) :n1,n2s/word1/word2/g：n1与n2为数字，在第n1行与n2行之间寻找word1这个字符串，并将该字符串替换为word2
        (19) :1,$s/word1/word2/g：将全文的word1替换为word2
        (20) :1,$s/word1/word2/gc：将全文的word1替换为word2，且在替换前要求用户确认。
        (21) v：选中文本
        (22) d：删除选中的文本
        (23) dd: 删除当前行
        (24) y：复制选中的文本
        (25) yy: 复制当前行
        (26) p: 将复制的数据在光标的下一行/下一个位置粘贴
        (27) u：撤销
        (28) Ctrl + r：取消撤销
        (29) 大于号 >：将选中的文本整体向右缩进一次
        (30) 小于号 <：将选中的文本整体向左缩进一次
        (31) :w 保存
        (32) :w! 强制保存
        (33) :q 退出
        (34) :q! 强制退出
        (35) :wq 保存并退出
        (36) :set paste 设置成粘贴模式，取消代码自动缩进
        (37) :set nopaste 取消粘贴模式，开启代码自动缩进
        (38) :set nu 显示行号
        (39) :set nonu 隐藏行号
        (40) gg=G：将全文代码格式化
        (41) :noh 关闭查找关键词高亮
        (42) Ctrl + q：当vim卡死时，可以取消当前正在执行的命令
    异常处理：
        每次用vim编辑文件时，会自动创建一个.filename.swp的临时文件。
        如果打开某个文件时，该文件的swp文件已存在，则会报错。此时解决办法有两种：
            (1) 找到正在打开该文件的程序，并退出
            (2) 直接删掉该swp文件即可
    ```
16. less/tail/more/head
    ```
    more           浏览文件内容，回车下一行，空格下一页，b上一页，q退出
    less           同more，额外的，y上一行，page down下一页，page up上一页
    head -3 xxx    查看xxx文件头3行
    tail -3 xxx    查看xxx文件尾3行
    ```
17. diff xxx yyy：比较xxx和yyy文件的不同处
18. grep/fgrep xxx：查找包含xxx的行
19. kill -9 pid：杀死pid进程
    - kill -s SIGTERM pid：传递具体的信号
20. ps aux：显示所有用户的所有进程的详细信息
    - 这里 a 显示所有用户的进程，u 以用户为中心显示，x 显示没有控制终端的进程。
21. df -h：查看硬盘使用情况
22. free -h：查看内存使用情况
23. du -h：查看当前目录占用的进程空间
24. top：查看所有进程信息， M按内存排序，P按cpu排序，q退出
25. ping xxx.com：查看是否联网
26. chmod：修改文件权限
    ```
    chmod +x yyy
    chmod -x yyy
    chmod 777 xxx
    chmod 777 yyy
    wrx
    ```
27. tree：展示当前目录结构
    ```
    tree xxxx   展示xxxx目录的文件结构
    tree -a     展示隐藏文件
    ```
28. find xxxx -name '*.py'：查找xxx路径下所有python文件
29. chown xxx yyy：将文件yyy的所有者改为xxx
30. sort xxx：对文件xxx按字典序排序，可以指定排序规则
31. sudo：root身份执行命令
32. tar：压缩与解压
    ```
    tar -zcvf xxx.tar.gz xxxx    压缩
    tar -zxvf xxxx.tar.gz        解压
    ```
33. apt-get install xx：安装xx软件
34. pip install xxx --user --upgrage：安装python包
35. cut：分割一行内容
    ```
    echo $PATH | cut -d ':' -f 3,5：输出PATH，用:分割后第3、5列数据
    echo $PATH | cut -d ':' -f 3-5：输出PATH，用:分割后第3-5列数据
    echo $PATH | cut -c 3,5：输出PATH的第3、5个字符
    echo $PATH | cut -c 3-5：输出PATH的第3-5个字符
    ```
36. yum install [package_name]：安装包
37. watch -n 0.1 [command]：每0.1秒执行一次该命令
38. history：查看命令历史
39. wc：统计信息
    ```
    wc -l     统计行数
    wc -w     统计单词数
    wc -c     统计字节数
    ```
40. netstat -nt：查看所有网络链接
41. awk：文本处理工具，功能很多，用时再搜
42. w：列出当前登录用户
43. time [command]：统计命令执行时间
44. nohup [command] &：后台执行命令
45. env：显示环境变量
46. ipython3：交互式python3环境。可以当做计算器，或者批量管理文件。
    - ! echo "Hello World"：!表示执行shell脚本

## 一些实操linux命令
1. 查询某个时间段内日志的数量
    ```
    cat xxx.log | grep 16:3[0-9] | wc -l
    ```
2. 统计当前目录下，所有python文件的总行数
    ```
    find . -name '*.py' | xargs cat | wc -l
    ```
3. 显示第二行、最后一行，查找以.c结尾的文件怎么找
    ```
    head -2 xxx.log | tail -1
    tail -1 xxx.log
    find *.c
    ```
4. 根据diff_sum拆分左右，左边的就是$1,右边的就是$2，这里取出右边，然后取出右边的第一个参数进行计算
    ```
    cat video_ura_diff.log | grep "diff率" | grep -E 
    '\[2024-07-08(12:1[0-9]:|12:[2-5][0-9]:|1[3-9]:|2[0-3]:)[0-5][0-9]:[0-5][0-9]\]' | 
    awk -F"diff_sum=" '{print $2}' | awk '{sum += $1} END {print sum}'
    -- sum/NR就是求平均值
    ```
5. 查看某端口是否使用
    ```
    sudo netstat -tuln | grep :<端口号>
    sudo ss -tuln | grep :<端口号>
    sudo lsof -i:<端口号>
    sudo fuser <端口号>/tcp

    这些命令可以显示当前占用指定端口的进程或网络连接。
    如果端口被占用，这些命令会输出相关信息；如果没有被占用，则没有输出。
    ```