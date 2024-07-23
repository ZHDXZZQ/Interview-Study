package const_test

import "testing"

const (
	Monday = iota + 1
	Tuesday
	Wednesday
)

// const (
// 	Monday = 1
// 	Tuesday = 2
// 	Wednesday = 3
// )

const (
	Readable = 1 << iota	// 和 iota << 1大不相同，iota本身是0，每一行会+1，比如现在是1<<1，下一行就是1<<2
	Writable	// 2
	Executable	// 4
)

func TestConst (t *testing.T) {
	t.Log(Monday, Tuesday)
}

func TestConst2 (t *testing.T) {
	a := 7 // 0111
	t.Log(a & Readable == Readable, a & Writable == Writable, a & Executable == Executable)

	a = 5 // 0101
	t.Log(a & Readable == Readable, a & Writable == Writable, a & Executable == Executable)

	t.Log(Readable, Writable, Executable)
}