package concurrent_test

import (
	"sync"
	"testing"
	"time"
)

// Mutex
func TestSharedMemory(t *testing.T) {
	counter := 0
	for i := 0; i < 5000; i ++ {
		go func() {
			counter ++
		}()
	}
	time.Sleep(1 * time.Second)
	t.Logf(" counter = %d", counter)	// 不安全，值不为5000
}

func TestCounterThreadSaft(t *testing.T) {
	var mut sync.Mutex
	counter := 0
	for i := 0; i < 5000; i ++ {
		go func() {
			defer func() {	// 使用defer保证释放锁，避免异常导致锁未释放
				mut.Unlock()
			}()
			mut.Lock()
			counter ++
		}()
	}
	time.Sleep(1 * time.Second)	// 如果不sleep可能导致一些协程未执行完导致结果错误
	t.Logf(" counter = %d", counter)	
}

// WaitGroup
func TestCounterWaitGroup(t *testing.T) {
	var mut sync.Mutex
	var wg sync.WaitGroup
	counter := 0
	for i := 0; i < 5000; i ++ {
		wg.Add(1)		// 添加一个任务
		go func() {
			defer func() {	// 使用defer保证释放锁，避免异常导致锁未释放
				mut.Unlock()
			}()	// 注意defer也是执行一个函数，因此也要有个参数传递的口
			mut.Lock()
			counter ++
			wg.Done()	// 完成一个任务
		}()
	}
	wg.Wait()	// 等待每个协程执行结束
	t.Logf(" counter = %d", counter)	
}

// RWMutex提供了以下方法：

// Lock(): 获取写锁定。阻塞直到获得锁定。
// Unlock(): 释放写锁定。
// RLock(): 获取读锁定。阻塞直到获得锁定。
// RUnlock(): 释放读锁定。