/*
panic用于不可恢复的错误
panic退出前会执行defer的内容，会输出堆栈信息

os.Exit退出时不会调用defer，也不会输出当前的调用堆栈信息

recover 类似于 try catch
会返回一个错误，即panic里面传入的错误，不会中断程序
当心形成僵尸服务程序，导致health check失效，即进程还存在，但是无法提供服务，比如没有资源可用但recover了
let it crash！被crash掉后，守护进程会重新启动服务进程，这是一种可恢复的设计模式
*/

package err_test

import (
	"testing"
	"fmt"
	"errors"
	// "os"
)

func TestPanic (t *testing.T) {
	defer func() {
		fmt.Println("[ZZQ DEBUG] exec here")
	} ()

	defer func() {
		if err := recover(); err != nil {
			fmt.Println("recovered panic from err: ", err)
		}
	} ()

	fmt.Println("[ZZQ DEBUG] START")
	
	panic(errors.New("Something wrong!"))
	
	// os.Exit(-1)	// os 退出不会执行defer
	
	fmt.Println("[ZZQ DEBUG] END")	// 都不会执行到
}