/*

1. go没有异常机制，依赖于返回值的判断
通过多返回值回传err

2. error类型实现了error接口
type error interface {
	Error() string
}

3. 可以通过errors.New来快速创建错误实例
errors.New("n must be in the range [0, 10]!")

*/

// 尽早失败，避免嵌套，每步判nil，有错就return

package err_test

import (
	"testing"
	"errors"
	"fmt"
)

var LessThanTwoEroor = errors.New("n must be greater than 2")
var GreaterThanHundredError error = errors.New(" n must be less than 100")

func GetFib(n int) ([]int, error) {
	// if n < 2 || n > 100 {
	// 	return nil, errors.New("n should be in [2, 100]")
	// }

	if n < 2 {
		return nil, LessThanTwoEroor
	}

	if n > 100 {
		return nil, GreaterThanHundredError
	}

	fib_list := []int{1, 1}

	for i := 2; i < n; i ++ {
		fib_list = append(fib_list, fib_list[i - 1] + fib_list[i - 2])
	}
	return fib_list, nil
}

func TestGetFib(t *testing.T) {
	if v, err := GetFib(-10); err != nil {
		t.Error(err)
	} else {
		t.Log(v)
	}

	if list, err := GetFib(101); err != nil {
		if err == LessThanTwoEroor {
			t.Error("Need a larger number")
			fmt.Println("it is so less")
		} else if err == GreaterThanHundredError {
			t.Error("Need a larger number")
			fmt.Println("it is so big")
		} else {
			t.Error(err)
		}
	} else {
		t.Log(list)
	}
	
}