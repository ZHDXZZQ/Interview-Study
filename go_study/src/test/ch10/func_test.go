/*
函数：一等公民
1. 函数可以返回多个值
2. 所有参数都是值传递：slice，map，channel会有引用的错觉
3. 函数可以作为变量的值
4. 函数可以作为参数和返回值
*/

package test_func

import (
	"testing"
	"math/rand"
	"fmt"
	"time"
)

func returnMuilt() (int, int) {
	return rand.Intn(10), rand.Intn(20)
}

// 对特定类型的函数进行时间计算，返回值是一个函数，参数是int，返回值是int
func timeSpent (inner func (op int) int) func (op int) int {	// 传一个inner的函数进来，inner函数的参数是int，返回类型是int
	return func(n int) int {	// 返回一个函数，会执行inner函数，并记录时间
		start := time.Now()
		ret := inner(n)
		fmt.Println("time spent: ", time.Since(start).Seconds())
		return ret
	}
}

func slowFunc (op int) int {
	time.Sleep(time.Second * 1)
	return op
}

func TestFunc (t *testing.T) {
	a, b := returnMuilt()
	t.Log(a, b)
	_, c := returnMuilt()
	t.Log(c)

	tssf := timeSpent(slowFunc)	// 计算耗时函数tssf
	t.Log(tssf(10))
}