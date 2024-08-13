/*
	csp:communicating sequential processes
	依赖于通道完成通讯实体间的协调
	1. 和actor model的直接通讯不同，csp模式是通过channel完成的，更松耦合
	2. go的channel是有容量限制，且独立于处理Groutine，协程会主动处理；而如Erlang和Actor模式中的mailbox容量是无限的，且接收进程也是被动处理消息的
*/

/*
	Channel
	1. channel的接收方会阻塞，直到消息到来
	2. buffer channel可以设置容量，类似生产者消费者模式
*/

package channel_test

import (
	"fmt"
	"testing"
	"time"
)

func service() string {
	fmt.Println("sleep 50 ms")
	time.Sleep(time.Millisecond * 50)
	fmt.Println("awake 50 ms")
	return "done"	// 4
}

func otherTask() {
	fmt.Println("working on something else")	// 1
	fmt.Println("sleep 100 ms")
	time.Sleep(time.Millisecond * 100)
	fmt.Println("awake 100 ms")
	fmt.Println("Task is Done")	// 3
}

// func TestService(t *testing.T) {
// 	fmt.Println(service())
// 	otherTask()
// }

func AsyncService() chan string {
	// retch := make(chan string)
	retch := make(chan string, 1)	// buffer channel，收到指定数量的消息后可以立即结束协程，不会阻塞
	go func() {
		ret := service()
		fmt.Println("returned result")	// 2
		retch <- ret 		// 会阻塞在channel的消息传递的过程中，取出数据放入channel
		fmt.Println("service exited.")	// 5
	} ()
	return retch
}

func TestAsyncService(t *testing.T) {
	retch := AsyncService()
	otherTask()
	fmt.Println(<-retch)	// 从channel取数据
	fmt.Println("sleep 1 s")
	time.Sleep(time.Second * 1)
	fmt.Println("awake 1 ms")
}