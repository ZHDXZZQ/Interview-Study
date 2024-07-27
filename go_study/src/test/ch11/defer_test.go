/*
可变长参数：类型一致，不指定个数，转换成数组，变成数组遍历来运行
defer：延迟执行函数，即便遇到panic也会执行，对于defer嵌套是一个栈，对于顺序的defer也是一个栈，一般用于上报和解锁
*/

package defer_test

import (
	"testing"
	"fmt"
)

func Sum(ops ...int) int {
	ret := 0
	for _, op := range ops {
		ret += op
	}
	return ret
}

func TestVarParams (t *testing.T) {
	t.Log(Sum(1, 2, 3, 4))
	t.Log(Sum(1, 2, 3, 4, 5, 6))
}


func Clear2() {
	fmt.Println("clear2 resources.")
}

func Clear() {
	defer Clear2()
	fmt.Println("clear resources.")
}

func TestDefer (t *testing.T) {
	defer Clear()
	// defer Clear2()
	fmt.Println("start")
	// panic("error")
	// fmt.Println("end")
}