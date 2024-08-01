/*

循环仅支持for循环
	for i := 1; i < n; i ++ {
		...
	}

	n := 0
	for n < 5 {
		...
	}

	n := 0
	for {
		...
	}

*/

package testloop

import "testing"

func TestLoop (t *testing.T) {
	n := 0
	for n < 5 {
		t.Log(n)
		n ++
	}
}

/*
判断语句，条件必须是一个bool类型，支持变量赋值
	if var declaration; condition {
		...
	} else if condition2 {
		...
	} else {
	 	...
	}
*/

func TestIF (t *testing.T) {
	if a := 1 == 1; a {		// a一定是个bool值，不能是1或0
		t.Log("1 == 1")
	}

	// 函数多返回值样例
	// if v, err := somefunc(); err == nil {
	// 	t.Log("do some thing")
	// } else {
	// 	t.Log("error")
	// }
}

/*
switch语句
1. 条件表达式无限制为常量或整数
2. 单个case中可以有多个结果选项，用逗号分隔
3. 与C语言相反，不需要break来退出case，注意区分C++和python在这块的不同
4. 可以不设定switch后的条件表达式，这样的switch类似于if else语句

	switch os := runtime.GOOS; os {
		case "darwin":		// 支持任意类型
			fmt.Println("os x.")
			// break	自带break
		case "linux":
			fmt.Println("linux.")
		default:
			fmt.Printf("%s.", os)
	}

	switch {		// 支持多条件命中
		case 0 <= num && num <= 3:
			fmt.Printf("0 - 3")
		case 4 <= num && num <= 6:
			fmt.Printf("4 - 6")
		case 7 <= num && num <= 9:
			fmt.Printf("7 - 9")
	}
*/

func TestSwitch (t *testing.T) {
	for i := 0; i < 5; i ++ {
		switch i {
		case 0, 2:
			t.Log("Even")
		case 1, 3:
			t.Log("Odd")
		default:
			t.Log("unknown")
		}
	}
	t.Log("---------------------")
	for i := 0; i < 5; i ++ {
		switch {
		case i % 2 == 0:
			t.Log("Even")
		case i % 2 == 1:
			t.Log("Odd")
		default:
			t.Log("unknown")
		}
	}
}