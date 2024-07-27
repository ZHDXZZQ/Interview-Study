/*
	函数是一等公民，也与其他类型相同
	因此map的value可以是一个方法，与go的dock type接口方式一起可以实现简单的单一方法对象的工厂模式
*/

package test_map_fac_set

import "testing"

func TestMapWithFunc(t *testing.T) {
	m := map[int]func(op int)int{}	// func(参数)返回值{}
	m[1] = func(op int) int { return op }
	m[2] = func (op int) int { return op * op}
	m[3] = func (op int) int { return op * op * op}
	t.Log(m[1](2), m[2](2), m[3](2))
	t.Log(m[1](m[2](3)))
}

/*
	map实现set，go没有内置set，可以用map[type]bool实现
	保证元素的唯一性，可以添加元素、判断元素是否存在，删除元素，统计元素个数
*/

func TestSet (t *testing.T) {
	mySet := map[int]bool {}
	mySet[1] = true		// 插入元素
	if mySet[1] {		// 判断元素是否存在
		t.Log("key 1 is existing")
	} else {
		t.Log(" key 1 is not existing ")
	}
	n := 3
	if mySet[n] {
		t.Logf("key %d is existing", n)
	} else {
		t.Logf("key %d is not existing", n)
	}
	t.Log(len(mySet))
	mySet[3] = true
	mySet[5] = true
	n = 5
	if mySet[n] {
		t.Logf("key %d is existing", n)
	} else {
		t.Logf("key %d is not existing", n)
	}
	t.Log(len(mySet))	// 统计元素个数
	delete(mySet, 5)	// 删除元素
	n = 5
	if mySet[n] {
		t.Logf("key %d is existing", n)
	} else {
		t.Logf("key %d is not existing", n)
	}
	t.Log(len(mySet))
}