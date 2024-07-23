package main

import (
	"go_study/src/hello"
	"os"
	"fmt"
)

// main函数不支持arg []string之类的参数传入，而是直接通过os.Args获取命令行参数
func main() {	// 入口必须是main包的main方法，但是文件名不需要是main.go
	fmt.Println(os.Args)
	if len(os.Args) > 1 {	// 大括号在同一行
		fmt.Println("hello world", os.Args[1])
	}
	hello.Hello()	// 不支持任何返回值
	// 通过os.Exit返回状态
	os.Exit(0)	// -1为一种错误码
}