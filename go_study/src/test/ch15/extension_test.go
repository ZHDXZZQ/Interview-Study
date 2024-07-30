/*
	面向对象的扩展，go不支持继承
*/

package extension

import (
	"testing"
	"fmt"
)

type Pet struct {

}

func (p *Pet) Speak() {
	fmt.Print("...")
}

func (p *Pet) SpeakTo(host string) {
	p.Speak();
	fmt.Println(" ", host)
}

// 扩展类型，子类可以调用父类的接口，通过结构体内包含一个父类实现
// type Dog struct {
// 	p *Pet
// }

// func (d *Dog) Speak() {
// 	d.p.Speak()
// }

// func (d *Dog) SpeakTo(host string) {
// 	d.p.SpeakTo(host)
// }

// 当然也可以重新定义同名函数，因为属于不同的结构体
// func (d *Dog) Speak() {
	// fmt.Println("wang!")
// }

// func (d *Dog) SpeakTo(host string) {
	// d.Speak();
	// fmt.Println(" ", host)
// }

// 只写另一个类型，这样调用的方法就是Pet类型的方法
type Dog struct {
	Pet
}

// 重载无效，不支持重载，也不支持子类转换，但是支持重写
func (d *Dog) Speak() {
	fmt.Print("wang!")
}

func TestExtension (t *testing.T) {
	// dog := new(Dog)
	// dog.SpeakTo("zzq")

	// var dog Pet := new(Dog)		// 不支持类型转换
	// dog.SpeakTo("Zzq")

	dog:= new(Dog)
	dog.SpeakTo("132")
}