/*
	线程Thread vs 协程Groutine
	1. 线程默认stack大小为1M，协程为2K
	2. 与KSE kernel space entity的关系，线程为1：1，协程为m：n，协程的内核切换开销更少
	MPG，注意当长时间运行时，或IO中断时的处理机制
*/

package goroutine_test

import (
	"fmt"
	"time"
	"testing"
)

func TestGroutine (t *testing.T) {
	for i := 0; i < 10; i ++ {
		go func(i int) {
			fmt.Println(i)
		}(i)	// 值传递，如果不传i会有竞争关系，需要锁，否则值就不一定了，如下

		go func() {
			t.Log(i)
		} ()
	}
	time.Sleep(time.Millisecond * 50)
}