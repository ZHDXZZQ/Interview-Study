/*
map的声明
m := map[string]int{"one": 1, "two": 2}
m1 := map[string]int{}
m1["one"] = 1
m2 := make(map[string]int, 10)		// capacity
*/

package test_map

import "testing"

func TestInitMap (t *testing.T) {	// 一定要驼峰式？不然不输出
	m := map[string]int{"one": 1, "two": 2}
	t.Log(m["two"], len(m))

	m1 := map[string]int{}
	m1["one"] = 1
	t.Log(m1["one"], len(m1))

	m2 := make(map[string]int, 10)
	t.Logf("len 3 = %d", len(m2))
	// 不支持访问cap(m2)
}

func TestAccessNotExistringKey (t *testing.T) {
	m1 := map[int]int{}
	t.Log(m1[1])		// 默认0值，不会返回nil
	m1[2] = 0
	t.Log(m1[2])
	if v, ok := m1[3]; ok {	// 判断key是否存在，避免被默认0值干扰
		t.Logf("key 3 value is %d", v)
	} else {
		t.Log("key 3 is not existing")
	}
}

/*	
	遍历
*/

func TestTravelMap (t *testing.T) {
	m1 := map[int]int{1: 1, 2: 4, 3: 9}
	for k, v := range m1 {
		t.Log(k ,v)
	}
}