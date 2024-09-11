package task_test

import(
	"fmt"
	"testing"
	"time"
)

func isCancelled(cancelChan chan struct{}) bool {
	select{
	case <- cancelChan:		// 检查此时是否有消息
		return true
	default:	// cancelChan没有消息时，返回false表示没有被取消
		return false
	}
}

func cancel_1(cancelChan chan struct{}) {
	cancelChan <- struct{}{}	// 向 cancelChan 发送一个空结构体（struct{}{}）作为取消信号。
	// 注意：此方法只能用在通道未关闭的情况下。如果通道已经关闭，发送消息会导致 panic。
}

func cancel_2(cancelChan chan struct{}) {
	close(cancelChan)	// 一旦通道被关闭，所有试图向这个通道发送数据都会导致 panic。关闭通道是一个通知所有接收者该通道不再会有更多的数据。
}

func TestCancel(t *testing.T) {
	cancelChan := make(chan struct{}, 0)	// 一个缓冲区大小为 0 的通道，用于传递取消信号。
	for i := 0; i < 5; i ++ {	//  起5个协程
		go func(i int, cancelCh chan struct{}) {	// 入参
			for {	// 每个协程每5毫秒检查一次是否通道被取消
				if isCancelled(cancelCh) {
					break
				}
				time.Sleep(time.Millisecond * 5)
			}
			fmt.Println(i, "Done Cancelled")
		}(i, cancelChan)	// 传入参数
	}
	cancel_1(cancelChan)	// 只能通知1个协程被取消，其他的还在阻塞检查
	cancel_2(cancelChan)	// 全部关闭
	time.Sleep(time.Second * 1)
}

/*
在 Go 中，`make(chan struct{}, 0)` 和 `make(chan struct{})` 是等效的，都是创建一个**无缓冲通道**（unbuffered channel）。这里的 `0` 明确指定了通道的缓冲区大小为零。接下来详细解释有无 `0` 的区别和通道缓冲机制：

### 无缓冲通道 (`make(chan struct{})` 或 `make(chan struct{}, 0)`)

- **定义**：创建了一个无缓冲通道。无缓冲意味着只有当发送方和接收方同时准备好时，数据才能被传输。
- **发送和接收**：
  - **发送方**会阻塞，直到有一个接收方来接收数据。
  - **接收方**会阻塞，直到有一个发送方发送数据。
- **同步机制**：无缓冲通道是一个**同步**机制，保证了发送和接收操作的同步执行。

### 有缓冲通道 (`make(chan struct{}, n)`，`n > 0`)

- **定义**：创建一个带有缓冲区的通道，缓冲区大小为 `n`。
- **发送和接收**：
  - **发送方**会在缓冲区未满时将数据放入缓冲区而不阻塞。
  - **接收方**在缓冲区未空时可以直接获取数据而不阻塞。
- **异步机制**：缓冲区的存在使得发送和接收可以在一定程度上异步执行，直到缓冲区被填满或清空。

### 0和其他缓冲区大小的区别

- `make(chan struct{}, 0)`：无缓冲通道，与 `make(chan struct{})` 效果相同，必须同步进行传输。
- `make(chan struct{}, n)` (`n > 0`)：有缓冲通道，允许 `n` 个元素异步发送。

### 使用场景

- **无缓冲通道**：用于强同步需求的场景，保证发送方和接收方必须同时就绪。例如，执行一个任务后立即等待结果。
- **有缓冲通道**：用于允许一定的异步操作，提升效率，适用于需要缓冲的场景，如批量任务处理等。

### 总结

在代码中使用 `make(chan struct{}, 0)` 明确指定了无缓冲机制，与 `make(chan struct{})` 本质上是一样的。选择哪种通道类型主要取决于程序的同步或异步需求。
*/