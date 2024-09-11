# docker相关操作
## 镜像
1. docker images：列出本地所有镜像
2. docker pull xxx：拉取xxx镜像
3. docker image rm xxx：删除xxx镜像
4. docker commit xxx image_name:tag：创建xxx的新镜像image_name:tag
5. docker save -o ubuntu_20_04.tar ubuntu:20.04：将镜像ubuntu:20.04导出到本地文件ubuntu_20_04.tar中
6. docker load -i ubuntu_20_04.tar：将镜像ubuntu:20.04从本地文件ubuntu_20_04.tar中加载出来
7. docker export -o xxx.tar yyy：将容器yyy导出到本地文件xxx.tar中
8. docker import xxx.tar image_name:tag：将本地文件xxx.tar导入成镜像，并将镜像命名为image_name:tag
    - docker export/import与docker save/load的区别：
        - export/import会丢弃历史记录和元数据信息，仅保存容器当时的快照状态
        - save/load会保存完整记录，体积更大

   
## 容器
1. docker create -it xxx：利用镜像xxx创建一个容器yyy
2. docker run --network=host -it --privileged -v /data/home/samszhang:/data/home/samszhang --name yyy xxxid /bin/bash
    - 首先找到本地的镜像id，利用xxx镜像的id创建一个容器yyy并运行，配置网络接口，文件夹对应位置和权限等
3. docker start/stop/restart yyy：启动/停止/重启容器yyy
4. docker ps -a：查看所有本地容器
5. docker attach yyy：进入容器yyy
    - ctrl+p，再按ctrl+q可以挂起容器
6. docker exec -it yyy bash：在容器yyy中执行命令，可以理解为进入容器
7. docker rm yyy：删除容器yyy
8. docker container prune：删除所有已停止容器
9. docker top yyy：查看yyy容器内所有进程
10. docker stats：查看所有容器的统计信息
11. docker cp xxx yyy:xxx：在本地和yyy容器间复制文件
12. docker rename yyy xxx：将容器yyy重命名为xxx
13. docker update xxx --memory 500MB：修改容器yyy的内存