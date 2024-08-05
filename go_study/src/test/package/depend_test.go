/*
	go未解决的依赖问题
	1. 同一环境下，不同项目使用同一包的不同版本
	2. 无法管理对包的特定版本的依赖

	vendor路径
	随着go 1.5 release的发布，vendor目录被添加到除了GOPATH和GOROOT之外的依赖目录查找的解决方案
	在go 1.6之前需要手动设置环境变量

	查找依赖包路径的解决方案：
	1. 当前包下的vendor
	2. 向上级目录查找，直到找到src下的vendor目录
	3. 在GOPATH下查找依赖包
	4. 在GOROOT下查找

	常用的依赖管理工具：godep、glide、dep等，在github上搜

	install glide
	glide init
	vim glide.yaml
	glide install   生成vandor目录，里面就会保存要引用的依赖了
*/