/*
数组
var a [3]int
a[0] = 1

b := [3]int{1, 2, 3}
c := [2][2]int{{1, 2}, {3, 4}}

截取，不支持-1
a[start:end)
a := [...]int{1, 2, 3, 4, 5}
a[1:2]			// 2
1[1:3]			// 2, 3
a[1:len(a)]		// 2, 3, 4, 5
a[1:]			// 2, 3, 4, 5
a[:3]			// 1, 2, 3
a[:]			// 1, 2, 3, 4, 5
*/

package test_arr

import "testing"

func TestArrSlice (t *testing.T) {
	var arr [3]int32
	arr1 := [4]int{1, 2, 3, 4}
	arr3 := [...]int{1, 2, 3, 4, 5}
	arr1[1] = 5
	t.Log(arr[1], arr[2])
	t.Log(arr1, arr3)

	t.Log("--------")

	for i := 0; i < len(arr3); i ++ {
		t.Log(arr3[i])
	}
	t.Log("--------")
	for index, val := range arr3 {	// 对于不用的变量，需要用_忽略
		t.Log(index, val)
	}
}

/*
切片slice，其实就是vector的指针，是一个共享的存储结构，实现可变长的连续存储空间
是一个结构体，包含一个ptr，len，cap，即指向连续空间的指针，实际大小size，实际拥有空间capacity
切片只能够和nil进行比较，无法和数组和切片比较
*/

func TestSlice (t *testing.T) {
	var s []int 	//不填大小和...就是切片
	t.Log(len(s), cap(s))
	s = append(s, 1)
	t.Log(len(s), cap(s))

	s1 := []int{1, 2, 3, 4}
	t.Log(len(s1), cap(s1))

	s2 := make([]int, 3, 5)	// type len cap 默认值0
	t.Log(len(s2), cap(s2))
	t.Log(s2[0], s2[2])
	s2 = append(s2, 1)
	t.Log(s2[0], s2[2], s2[3])
	t.Log(len(s2), cap(s2))

}

func TestSliceGrowing (t *testing.T) {
	s := []int{}
	for i := 0; i <= 10; i ++ {	// cap以2倍扩大
		s = append(s, i)
		t.Log(len(s), cap(s))
	}
}

func TestSliceShared (t *testing.T) {
	months := []string{"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"}
	t.Log(len(months), cap(months))
	q2 := months[3 : 6]
	t.Log(len(q2), cap(q2))
	summer := months[5 : 8]
	t.Log(len(summer), cap(summer))
	summer[0] = "zzq--test"
	t.Log(q2)
	t.Log(months)
	t.Log(summer)
}