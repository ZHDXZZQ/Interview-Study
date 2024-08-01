package test_self_type

import (
	"testing"
	"time"
	"fmt"
)


// 对特定类型的函数进行时间计算，返回值是一个函数，参数是int，返回值是int
// func timeSpent (inner func (op int) int) func (op int) int {	// 传一个inner的函数进来，inner函数的参数是int，返回类型是int
// 	return func(n int) int {	// 返回一个函数，会执行inner函数，并记录时间
// 		start := time.Now()
// 		ret := inner(n)
// 		fmt.Println("time spent: ", time.Since(start).Seconds())
// 		return ret
// 	}
// }

type IntConv func (op int) int	// 起别名，自定义类型
// type myint int

func timeSpent (inner IntConv) IntConv {	// 返回类型也可以是func (a int) int 因为没有隐式类型转换，只是为了表明类型，可以替换
	return func(n int) int {	// 这里不能替换，因为内部的n无法找到
		start := time.Now()
		ret := inner(n)
		fmt.Println("time spent: ", time.Since(start).Seconds())
		return ret
	}
}

func slowFunc (op int) int {	// IntConv
	time.Sleep(time.Second * 1)
	return op
}

func TestFunc (t *testing.T) {
	tssf := timeSpent(slowFunc)	// 计算耗时函数tssf
	t.Log(tssf(10))
}