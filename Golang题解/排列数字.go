/*
    思路： dfs回溯，时间On!，空间On递归栈空间
    1. 用一个数组切片存当前结果
    2. 用一个map记录当前没有用哪些数字来提速
    3. 每次插入未插入的数字，如果个数不够，就接着dfs插入
    4. 如果个数满足，则打印当前数字
    5. 每次dfs完之后要回溯
*/

package main

import (
	"fmt"
	"sort"
)

var curRes []int
var unusedNum map[int]bool

func dfs(n int) {
	if len(curRes) == n {	// 如果个数满足n，就打印当前结果
		for _, x := range curRes {
			fmt.Print(x, " ")
		}
		fmt.Println()
		return
	}

	// 将未使用的数字收集到一个切片中，以便遍历
	candidates := []int{}
	for num := range unusedNum {
		candidates = append(candidates, num)
	}
	sort.Ints(candidates) // 确保遍历的顺序一致

	for _, num := range candidates {	// 遍历所有未插入的数字
		curRes = append(curRes, num)
		delete(unusedNum, num)
		dfs(n)
		unusedNum[num] = true	// 回溯
		curRes = curRes[:len(curRes)-1]	// 弹出上一个数
	}
}

func main() {
	var n int
	fmt.Scan(&n)
	unusedNum = make(map[int]bool)
	for i := 1; i <= n; i++ {
		unusedNum[i] = true
	}
	dfs(n)
}
