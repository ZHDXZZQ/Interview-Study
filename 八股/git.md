# git相关操作
1. git checkout
    ```
    git checkout -b xxx          创建并切换到xx分支
    git checkout - xx            将xx文件尚未加入暂存区的修改全部撤销
    git restore xx               将xx文件尚未加入暂存区的修改全部撤销
    git checkout xx              切换到xx分支
    git checkout -t origin/xx    远程的xx分支拉到本地
    ```
2. gid add：添加文件到暂存区
    ```
    gid add .
    git add xxx
    ```
3. git commit：提交到当前分支
    ```
    git commit -m "[feat]..." -n
    -n可以跳过检查
    ```
4. git push
    ```
    git push              将当前分支推送到远程仓库
    git push --set-upstream origin xxxx    设置本地的分支对应远程仓库的xxx分支
    git push -f           强制推送
    git push -u           将当前分支推送到远程仓库，首次需要
    git push origin xx    将本地xx分支推送到远程
    ```
5. git pull
    ```
    git pull                将远程仓库的当前分支与本地仓库的当前分支合并
    git pull origin master
    git pull origin xxx     将远程仓库xx分支与当前分支合并
    ```
6. git stash
    ```
    git stash        暂存修改和提交
    git stash pop    弹出暂存，同时清空栈顶
    git stash apply  弹出暂存，但栈顶还在
    git stash drop   删除栈顶的暂存修改
    git stash list   查看栈中所有元素
    ```
7. git clone xxx：克隆仓库到当前目录
    - 也可以克隆指定分支
    - 也可以将克隆的项目以别名存储
8. git init：当前目录配置成git仓库
9. git branch
    ```
    git branch         查看所有分支和当前分支
    git branch -d xxx  删除本地的xx分支  
    git branch xxx     创建新分支xxx
    git branch --set-upstream-to=origin/branch_name1 branch_name2 
    将远程的branch_name1分支与本地的branch_name2分支对应
    ```
10. git log：查看当前分支的所有版本提交历史信息
11. git diff xx：xx文件相对于暂存区有哪些改动
12. git status：查看仓库状态
13. git reset
    ```
    git reset --hard HEAD^        回退到上一个版本
    git reset --hard HEAD~
    git reset --hard HEAD^^       回退到上两个版本
    git reset --hard HEAD~100     回退100个版本
    git reset --hard [commit_id]  回滚到指定提交版本
    ```
14. git remote add origin xxxx.git：将本地仓库关联到远程仓库
15. git merge xxx：将xxx分支合并到当前分支
    1. 创建一个新的合并提交，将两个分支的历史记录合并在一起。
16. git rebase：将本地提交重新应用到从远程分支派生的新基础提交上，从而避免合并提交，使历史记录更加线性。
17. git fetch：从远程仓库获取最新的更改
18. git config
    ```
    git config --global user.name xxx            设置全局用户名，信息记录在~/.gitconfig文件中    
    git config --global user.email xxx@xxx.com   设置全局邮箱
    git config pull.rebase false                 在git pull默认使用merge而不是rebase
    ```