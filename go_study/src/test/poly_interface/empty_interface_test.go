package duotai

// 空接口可以表示任何类型
// 通过断言来将空接口转换为指定类型
// v, ok := p.(int)	// ok = true时转换成功


// go倡导更小的接口定义，很多接口只包含一个方法，负担更轻，例如
// type Reader interface {
// 	Read (p []byte) (n int, err error)
// }
// type Writer interface {
// 	Write (p []byte) (n int, err error)
// }

// 较大的接口可以由多个小接口的定义组合而成，例如
// type ReadWriter interface {
// 	Reader
// 	Writer
// }

// 只依赖于必要功能的最小接口，提高复用性，例如
// func StoreData (reader Reader) error {
// 	如果Reader写成了ReadWriter，那么需要多实现一个Writer接口
// 	...
// }

import (
	"testing"
	"fmt"
)

func Dosome(p interface{}) {
	// if i, ok := p.(int); ok {
	// 	fmt.Println("Integer", i)
	// 	return
	// }
	// if s, ok := p.(string); ok {
	// 	fmt.Println("String", s)
	// 	return
	// }
	// fmt.Println("Unknow")

	// switch写法
	switch v := p.(type) {
	case int:
		fmt.Println("Integer", v)
	case string:
		fmt.Println("String", v)
	default:
		fmt.Println("Unknow")
	}
}

func TestEmpty(t *testing.T) {
	Dosome(10)
	Dosome("101")
	Dosome(1.1)
}