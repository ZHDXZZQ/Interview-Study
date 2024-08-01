/*
	多态的实现
*/

package duotai

import (
	"testing"
	"fmt"
)

type Code string

type Programmer interface {
	WriteHelloWorld() Code
}

type GoProgrammer struct {}

func (p *GoProgrammer) WriteHelloWorld() Code {
	return "fmt.Println(\"Hello world ! \")"
}

type JavaProgrammer struct {}

func (j *JavaProgrammer) WriteHelloWorld() Code {
	return "System.out.Println(\"Hello world ! \")"
}

func writeFirstProgram(p Programmer) {	// interface只能对应指针类型的实例，因此p必须为指针类型，这里为什么不能写成*Programmer？
	fmt.Printf("%T %v\n", p, p.WriteHelloWorld())
}

func TestPolymorphism(t *testing.T) {
	goprog := new(GoProgrammer)	// &GoProgrammer{}
	javaprog := new(JavaProgrammer)
	writeFirstProgram(goprog)
	writeFirstProgram(javaprog)
}
