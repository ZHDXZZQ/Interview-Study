// 运算符
// + - * / % ++ --	没有前置的++和--
// == != > < >= <=
// && || !
// & | ^ << >> 与 或 异或 左移 右移
// &^按位清零 ： 只要右边为1，结果一定为0。 右边如果为0，结果等于左边。	10-1 11-0 01-0 00-0
// 加等号变成赋值运算符

// == 比较数组
// 相同数组维数且每维元素个数相同的数组才可以比较
// 每个元素都相同的数组才相等

package test_operator

import "testing"

func TestCompareArray(t *testing.T) {
	a := [...]int{1, 2, 3, 4}
	b := [...]int{1, 5, 3, 4}
	// c := [...]int{1, 2, 3, 4, 5}
	d := [4]int{1, 2, 3, 4}
	t.Log(a == b)
	// t.Log(a == c)	// error size not match
	t.Log(a == d)
}

const (
	R = 1 << iota	// 1	0001
	W				// 2	0010
	E				// 4	0100
)

func TestBitClear(t *testing.T) {
	a := 7	// 0111
	a = a &^ R	// 按位清零
	a &^= E	// 按位清零且赋值
	t.Log(a & R == R, a & W == W, a & E == E)
}