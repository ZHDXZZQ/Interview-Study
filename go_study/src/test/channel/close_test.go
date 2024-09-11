/*
	channel的关闭
	- 向关闭的channel发送数据，会导致panic
	- v, ok <- ch;   ok为bool值，true表示正常接收，false表示通道关闭
	- 所有的channel接收者都会在channel关闭时，立刻从阻塞等待中返回且上述ok值为false
	- 这个广播机制常被利用进行向多个订阅者同时发送信号，如：退出信号
*/

package channel_test
import (
	"fmt"
	"testing"
	"sync"
)

func dataProducer(ch chan int, wg *sync.WaitGroup) {
	go func() {
		for i := 0; i < 10; i ++ {
			ch <- i
		}
		close(ch)
		// ch <- 11		// close 后会 panic
		wg.Done()
	}()
}

func dataReceiver(ch chan int, wg *sync.WaitGroup) {
	go func() {
		// for i := 0; i < 10; i ++ {
		for {
			if data, ok := <- ch; ok {	// 如果没有判断ok但通道被关闭，也会立即退出并返回0值。
				fmt.Println(data)
			} else {
				break
			}
		}
		wg.Done()
	}()
}

func TestCloseChannel(t *testing.T) {
	var wg sync.WaitGroup
	ch := make(chan int)
	wg.Add(1)
	dataProducer(ch, &wg)
	wg.Add(1)
	dataReceiver(ch, &wg)
	wg.Add(1)
	dataReceiver(ch, &wg)
	wg.Wait()
}