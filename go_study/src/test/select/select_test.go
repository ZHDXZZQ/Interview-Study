package select_test
/*
// 多路选择，跟顺序无关，如果有default，那么当case都阻塞的时候，会直接走default，否则会一直阻塞直到某个case返回
select {
case ret := <-retch1:
	t.Logf("result %s", ret)
case ret := <-retch2:
	t.Logf("result %s", ret)
default:
	t.Error("no one returned")
}

// 超时控制
select {
case ret := <- retch:
	t.Logf("result %s", ret)
case <-time.After(time.Second * 1):
	t.Error("time out")
}
*/


import (
	"fmt"
	"testing"
	"time"
)

func service() string {
	time.Sleep(time.Millisecond * 500)
	return "Done"
}

func AsyncService() chan string {
	retCh := make(chan string, 1)
	go func() {
		ret := service()
		fmt.Println("returned result.")
		retCh <- ret
		fmt.Println("service exited.")
	}()
	return retCh
}

func TestSelect(t *testing.T) {
	select {
	case ret := <- AsyncService():
		t.Log(ret)
	case <- time.After(time.Millisecond * 100):
		t.Error("time out")
	}
}