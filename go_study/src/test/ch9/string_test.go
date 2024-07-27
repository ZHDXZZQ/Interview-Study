/*
string是数据类型，不是引用或指针
string是只读的byte slice，len函数为它所包含的byte数，和实际的字符数量是不同的
string的byte数组可以存放任何数据，如可见字符汉字、英文，也已存放任意二进制数据

Unicode UTF-8
unicode是一个字符集
utf-8是unicode的存储实现（转换为字节序列的规则）
*/

package test_string

import (
	"testing"
	"strings"	// 两个新库
	"strconv"
)

func TestString (t *testing.T) {
	var s string
	t.Log(s)
	s = "hello"
	t.Log(len(s))
	// s[1] = '3'	// error 不可更改
	s = "\xE4\xB8\xA5"	// 可以存储任意二进制数据，严
	t.Log(s)
	s = "\xE5\x38\xA5\xBB"	// 随便存
	t.Log(s)
	t.Log(len(s))

	s = "中"
	t.Log(len(s))	// byte数  3

	c := []rune(s)	// 取出string中的unicode
	t.Log(len(c))		// 1
	// t.Log("rune size: ", unsafe.Sizeof(c[0]))
	t.Logf("中 unicode %x", c[0])	// %x求十六进制 4e2d
	t.Logf("中 UTF-8 %x", s)		// e4 b8 cd
}

func TestStringToRune (t *testing.T) {
	s := "中华人民共和国"
	for _, c := range s {
		t.Logf("%[1]c %[1]d", c)	// 都对应第一个参数，即[1]，指都对应c
	}
}

func TestStringFunc (t *testing.T) {
	s := "a, b, c"
	parts := strings.Split(s, ",")	// 按，分割
	for _, part := range parts {
		t.Log(part)
	}
	t.Log(strings.Join(parts, " - "))	// 以 - 拼接

	str := strconv.Itoa(10)	// 整型转string
	t.Log("str + ", str)

	if i, err := strconv.Atoi("10"); err == nil {	// string转整型，有多个返回值
		t.Log(10 + i)
	}
	
}