/*
	1. package是基本服用模块单元，函数以首字母大写来表明可被包外代码访问
	2. 代码的package可以和所在的目录不一致
	3. 同一目录的go代码的package名字要一致

	init 方法
	1. 在main执行之前，所有依赖的package的init方法都会被执行
	2. 不同包的init函数按照包导入的依赖关系决定执行顺序
	3. 每个包可以由多个init函数
	4. 包的每个源文件也可以由多个init函数

	go的map不是线程安全的，通常采用读写锁保证安全
	syncmap效率更高，更适合于多读（90%）的场景
	外部调用concurrent_map示例
	go get -u github.com/xxxx		
	-u是每次更新

	在自己的代码包提交到github上时，直接以代码路径开始，不要有src，直接写go源码即可
*/

package pack_test

import (
	// "go_study/src/test/package/server/series"	// 这里为什么不行了？mod到底是怎么用的？
	"testing"
)

// import cm "github.com/easierway/concurrent_map"	// 起别名cm


func TestPackage (t *testing.T) {
	// t.Log(series.GetFib(5))


	// m := cm.CreateConcurrentMap(99)
	// m.Set(cm.StrKey("key"), 10)
	// t.Log(m.Get(cm.StrKey("key")))
}