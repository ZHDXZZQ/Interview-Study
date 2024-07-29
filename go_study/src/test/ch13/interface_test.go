/*
duck type式接口实现

接口定义

type Programmer interface {
	WriteHelloWorld() Code
}

type GoProgrammer struct {

}

func (p *GoProgrammer) WriteHelloWorld() Code {
	return "fmt.Println(\" hello world zzq ! \")"
}
*/

// 接口为非入侵性，实现不依赖于接口定义
// 所以接口的定义可以包含在接口使用者包内

package test_interface

import(
	"testing"
	// "fmt"
)

type Programmer interface {
	WriteHelloWorld() string
}

type GoProgrammer struct {	
	// 实现了Programmer的接口，但是没有实现impl显式依赖绑定，即无继承override等
	// 使用了duck type鸭子类型，即看起来方法签名一样，则归类为同一类，接口和类没有先后顺序的限制
}

func (g *GoProgrammer) WriteHelloWorld() string {
	return "fmt.Println(\" hello world zzq ! \")"
}

func TestInterface (t *testing.T) {
	var p Programmer
	p = new (GoProgrammer)	// var p Programmer = &GoProgrammer{}
	t.Log(p.WriteHelloWorld())
}
// 接口变量，分为两部分： 对于var p Programmer = &GoProgrammer{}这个p来说
// 一个是类型，即struct信息，type GoProgrammer struct{}
// 一个是数据，即实例 &GoProgrammer{}
