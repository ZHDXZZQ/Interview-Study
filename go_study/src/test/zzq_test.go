// 声明变量的方式
package try_test    // 本目录下的包名

import (    // 导包，对于每个包，都会执行init()函数
        "fmt"
        "testing"
)

func TestFirstTry(t *testing.T) {    // 方法名，开头要大写才能被包外访问
        t.Log("TestFirstTry")
        var a int = 1    // 声明方式1，声明必须使用，否则报错
        // b int = 1    // 声明方式2
        // var b = 1    // 声明方式3
        // 集体声明
        // var (
        //     a int = 1
        //     b     = 1
        // )
        b := 1            // 声明方式4 自动类型推导
        for i := 0; i < 10; i++ {
                // fmt.Print(" ", b)    // 标准输出
                t.Log(" ", b)
                tmp := a
                a = b
                b = tmp + a
        }
        fmt.Println()
}

// a, b = b, a    // 交换两个值，无需中间变量，即可以在一个赋值语句中进行多个变量的赋值