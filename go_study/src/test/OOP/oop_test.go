/*
go是否面向对象？
yes and no，不支持继承，接口实现特殊

封装数据和行为
type Employee struct {
	Id		string
	Name	string
	Age 	int
}

初始化
e := Employee{"0", "bob", 20}
e1 := Employee {Name: "nike", Age: 30}
e2 := new (Employee)	//返回引用/指针，相当于 e2 := &Employee{}
e2.Id = "2"		// 通过实例访问成员不需使用->
e2.Age = 22
e2.Name = "Rose"
*/

package test_oop

import (
	"testing"
	"fmt"
	"unsafe"
)

type Employee struct {
	Id		string
	Name	string
	Age 	int
}

func (e *Employee) String() string {
	fmt.Printf("address is %x\n", unsafe.Pointer(&e.Name))
	return fmt.Sprintf("ID: %s, Name: %s, Age: %d", e.Id, e.Name, e.Age)
}

func (e Employee) String2() string {		// 实例成员会被拷贝
	fmt.Printf("address2 is %x\n", unsafe.Pointer(&e.Name))
	return fmt.Sprintf("ID: %s, Name: %s, Age: %d", e.Id, e.Name, e.Age)
}

func TestOOP (t *testing.T) {
	e := Employee{"0", "bob", 20}
	e1 := Employee {Name: "nike", Age: 30}
	e2 := new (Employee)	//返回引用/指针，相当于 e2 := &Employee{}
	e2.Id = "2"		// 通过实例访问成员不需使用->
	e2.Age = 22
	e2.Name = "Rose"

	t.Log(e)
	t.Log(e1)
	t.Log(e1.Id)
	t.Log(e2)
	t.Logf("e is %T", e)	// &e和e2是同类型
	t.Logf("e2 is %T", e2)
}

func TestStructOp (t *testing.T) {
	e := Employee{"0", "bob", 20}
	t.Log(e.String())
	fmt.Printf("address3 is %x\n", unsafe.Pointer(&e.Name))
	t.Log(e.String2())
	
	e1 := &Employee{"1", "zed", 30}	// 通过指针和实例都可以访问
	t.Log(e1.String())
	t.Log(e1.String2())
}