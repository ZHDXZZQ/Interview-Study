// 数据类型
// bool
// string
// int 8 16 32 64	默认为机器字长
// uint 8 16 32 64 uintptr
// byte	无符号8位整型uint8的别名
// rune	实际上是int32类型，表示Unicode字符，是存储字符的整数值
// float 32 64
// complex 64 128	复数
// * &

// 1. 不支持任何隐式类型转换
// 2. 别名和原类型也不能进行隐式类型转化

// math.MaxInt64
// math.MaxFloat64
// math.MaxInt32
// 在math包中可以用

package type_test

import (
	"testing"
	"math"
	// "fmt"	//只要声明了就必须使用 
)

type MYINT int64	// 定义别名

func TestImplicit(t *testing.T) {
	var a int = 1	// 这里其实是int64
	var b int64 = 2

	// b = a	// error 不支持隐式类型转换
	// fmt.Printf("%T", a)

	b = int64(a)	// true 显示类型转换
	t.Log(a, b)

	// var MYINT c	// 实际是int64
	// c = b	// error 别名也不行

	// var d int32 = 1
	// b = a		// error
}

// 3. 指针类型不支持指针运算
// 4. string是值类型，默认初始值为空字符串，不是nil

func TestPoint(t *testing.T) {
	a := 1
	a_ptr := &a	// 取地址，获取指针

	// a_ptr = a_ptr + 1	// error

	t.Log(a, a_ptr, *a_ptr)
	t.Logf("%T %T", a, a_ptr)
}

func TestString(t *testing.T) {
	var s string
	t.Log("*" + s + "*")
	t.Log(len(s))

	a := math.MaxFloat64
	t.Log(a)

	if s == "" {	// not use s == nil
		t.Log("zzq")
	}
}