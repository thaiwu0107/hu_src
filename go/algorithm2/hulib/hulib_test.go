package hulib

import (
	"math/rand"
	"testing"
)

// 性能测试
func Benchmark_CheckHu(b *testing.B) {
	cards := []int{
		3, 1, 1, 1, 1, 1, 1, 1, 3,
		0, 0, 0, 1, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0,
	}
	for i := 0; i < b.N; i++ {
		CheckHu(cards, rand.Intn(i+1))
	}
}

func Benchmark_CheckHu_258(b *testing.B) {
	cards := []int{
		0, 3, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 2, 0, 0, 0, 0, 0, 0, 0,
		0, 1, 0, 0, 0, 0, 2,
	}
	for i := 0; i < b.N; i++ {
		CheckHu_258(cards, rand.Intn(i+1))
	}
}

//基本逻辑测试
func Test_CheckHu(t *testing.T) {
	for _, unit := range []struct {
		cards    []int
		guiIndex int
		expect   bool
	}{
		{
			cards: []int{
				3, 3, 3, 1, 0, 0, 0, 0, 0,
				0, 0, 0, 1, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0,
			},
			guiIndex: 12,
			expect:   true,
		},

		{
			cards: []int{
				3, 3, 3, 1, 0, 0, 0, 0, 0,
				0, 0, 0, 1, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0,
			},
			guiIndex: 13,
			expect:   false,
		},

		{
			cards: []int{
				3, 1, 1, 1, 1, 1, 1, 1, 3,
				0, 0, 0, 1, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0,
			},
			guiIndex: 12,
			expect:   true,
		},

		{
			cards: []int{
				3, 0, 0, 0, 0, 0, 0, 0, 3,
				0, 1, 0, 0, 0, 0, 0, 0, 0,
				0, 3, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 1,
			},
			guiIndex: 34,
			expect:   false,
		},

		{
			cards: []int{
				3, 0, 0, 0, 0, 0, 0, 0, 3,
				0, 1, 0, 0, 0, 0, 0, 0, 0,
				0, 3, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 1,
			},
			guiIndex: 33,
			expect:   true,
		},

		{
			cards: []int{
				3, 0, 0, 0, 0, 0, 0, 0, 3,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 1, 0, 0, 0, 0, 1,
			},
			guiIndex: 33,
			expect:   true,
		},

		{
			cards: []int{
				3, 1, 1, 1, 1, 1, 1, 1, 3,
				0, 0, 1, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0,
			},
			guiIndex: 34,
			expect:   false,
		},

		{
			cards: []int{
				3, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 1, 1, 0, 0, 0, 0,
				0, 1, 1, 1, 0, 3, 0, 0, 0,
				0, 1, 0, 0, 0, 0, 2,
			},
			guiIndex: 33,
			expect:   true,
		},
	} {
		if actually := CheckHu(unit.cards, unit.guiIndex); actually != unit.expect {
			t.Errorf("unit: [%v], actually: [%v]", unit, actually)
		}
	}
}

func Test_CheckHu_258(t *testing.T) {
	for _, unit := range []struct {
		cards    []int
		guiIndex int
		expect   bool
	}{

		{
			cards: []int{
				0, 0, 0, 1, 0, 0, 0, 0, 0,
				0, 0, 0, 3, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 1,
			},
			guiIndex: 33,
			expect:   false,
		},

		{
			cards: []int{
				0, 1, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 3, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 1,
			},
			guiIndex: 33,
			expect:   true,
		},

		{
			cards: []int{
				0, 0, 0, 0, 1, 0, 0, 3, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 1,
			},
			guiIndex: 33,
			expect:   true,
		},

		{
			cards: []int{
				0, 0, 0, 2, 3, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0,
			},
			guiIndex: 34,
			expect:   false,
		},

		{
			cards: []int{
				0, 0, 0, 0, 3, 0, 0, 0, 0,
				0, 2, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0,
			},
			guiIndex: 34,
			expect:   true,
		},

		{
			cards: []int{
				0, 3, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 2, 0, 0, 0, 0, 0, 0, 0,
				0, 1, 0, 0, 0, 0, 2,
			},
			guiIndex: 33,
			expect:   true,
		},
	} {
		if actually := CheckHu_258(unit.cards, unit.guiIndex); actually != unit.expect {
			t.Errorf("unit: [%v], actually: [%v]", unit, actually)
		}
	}
}

func Test_Is_13_19(t *testing.T) {
	for _, unit := range []struct {
		cards    []int
		guiIndex int
		expect   bool
	}{
		{
			cards: []int{
				1, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 0, 0, 1, 0, 0, 0, 0, 1,
				1, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 1, 1, 1, 1, 1, 1,
			},
			guiIndex: 12,
			expect:   true,
		},

		{
			cards: []int{
				1, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 0, 0, 1, 0, 0, 0, 0, 1,
				1, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 1, 1, 1, 1, 1, 1,
			},
			guiIndex: 13,
			expect:   false,
		},

		{
			cards: []int{
				1, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 0, 0, 1, 0, 0, 0, 0, 1,
				1, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 1, 1, 1, 1, 1, 1,
			},
			guiIndex: 34,
			expect:   false,
		},

		{
			cards: []int{
				1, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 1, 1, 1, 1, 1, 2,
			},
			guiIndex: 34,
			expect:   true,
		},

		{
			cards: []int{
				1, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 1, 1, 1, 1, 1, 2,
			},
			guiIndex: 33,
			expect:   true,
		},

		{
			cards: []int{
				3, 1, 1, 1, 1, 1, 1, 1, 1,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 1,
			},
			guiIndex: 34,
			expect:   false,
		},
	} {
		if actually := Is_13_19(unit.cards, unit.guiIndex); actually != unit.expect {
			t.Errorf("Is_13_19 err, unit:[%v],actually:[%v]\n", unit, actually)
		}
	}
}

func Test_IsXiaoQiDui(t *testing.T) {
	for _, unit := range []struct {
		cards    []int
		guiIndex int
		expect   bool //是否是小七对
		expect2  int  //豪华个数
	}{
		{
			cards: []int{
				2, 2, 2, 2, 2, 2, 2, 2, 2,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0,
			},
			guiIndex: 34,
			expect:   true,
			expect2:  0,
		},

		{
			cards: []int{
				4, 4, 4, 0, 0, 0, 0, 0, 2,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0,
			},
			guiIndex: 34,
			expect:   true,
			expect2:  3,
		},

		{
			cards: []int{
				4, 2, 2, 0, 0, 0, 0, 0, 2,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 4,
			},
			guiIndex: 33,
			expect:   true,
			expect2:  3,
		},

		{
			cards: []int{
				4, 1, 3, 0, 0, 0, 0, 2, 2,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 2,
			},
			guiIndex: 33,
			expect:   true,
			expect2:  2,
		},

		{
			cards: []int{
				4, 4, 4, 1, 1, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0,
			},
			guiIndex: 34,
			expect:   false,
		},

		{
			cards: []int{
				3, 1, 1, 1, 1, 1, 1, 1, 1,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 3,
			},
			guiIndex: 33,
			expect:   false,
		},
	} {
		actually, actually2 := IsXiaoQiDui(unit.cards, unit.guiIndex)
		if actually == true {
			if actually != unit.expect || actually2 != unit.expect2 {
				t.Errorf("IsXiaoQiDui err, unit:[%v],actually:[%v],actually2:[%v]\n", unit, actually, actually2)
			}
		}

	}
}

func Test_IsPengPengHu(t *testing.T) {
	for _, unit := range []struct {
		cards    []int
		guiIndex int
		expect   bool
	}{
		{
			cards: []int{
				3, 3, 3, 3, 2, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0,
			},
			guiIndex: 34,
			expect:   true,
		},

		{
			cards: []int{
				4, 4, 4, 0, 0, 0, 0, 0, 2,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0,
			},
			guiIndex: 34,
			expect:   false,
		},

		{
			cards: []int{
				3, 2, 2, 2, 1, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 4,
			},
			guiIndex: 33,
			expect:   true,
		},

		{
			cards: []int{
				4, 3, 3, 0, 0, 0, 0, 0, 2,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 2,
			},
			guiIndex: 33,
			expect:   true,
		},

		{
			cards: []int{
				4, 4, 4, 1, 1, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0,
			},
			guiIndex: 34,
			expect:   false,
		},
	} {
		if actually := IsPengPengHu(unit.cards, unit.guiIndex); actually != unit.expect {
			t.Errorf("IsPengPengHu err, unit:[%v],actually:[%v]\n", unit, actually)
		}
	}
}

func Test_IsQingYiSe(t *testing.T) {
	for _, unit := range []struct {
		cards    []int
		guiIndex int
		expect   bool
	}{
		{
			cards: []int{
				3, 3, 3, 3, 1, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 1,
			},
			guiIndex: 33,
			expect:   true,
		},

		{
			cards: []int{
				3, 3, 3, 3, 1, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 1,
			},
			guiIndex: 34,
			expect:   false,
		},

		{
			cards: []int{
				3, 3, 3, 3, 2, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0,
			},
			guiIndex: 34,
			expect:   true,
		},

		{
			cards: []int{
				3, 3, 3, 3, 0, 0, 0, 0, 0,
				2, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0,
			},
			guiIndex: 34,
			expect:   false,
		},
	} {
		if actually := IsQingYiSe(unit.cards, unit.guiIndex); actually != unit.expect {
			t.Errorf("IsQingYiSe err, unit:[%v],actually:[%v]\n", unit, actually)
		}
	}
}

func Test_IsHunYiSe(t *testing.T) {
	for _, unit := range []struct {
		cards    []int
		guiIndex int
		expect   bool
	}{
		{
			cards: []int{
				3, 3, 3, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 1, 1,
			},
			guiIndex: 33,
			expect:   true,
		},

		{
			cards: []int{
				3, 3, 3, 3, 0, 0, 0, 0, 0,
				1, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 2,
			},
			guiIndex: 34,
			expect:   false,
		},

		{
			cards: []int{
				3, 3, 3, 3, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				2, 0, 0, 0, 0, 0, 0,
			},
			guiIndex: 34,
			expect:   true,
		},

		{
			cards: []int{
				3, 3, 3, 0, 0, 0, 0, 0, 0,
				2, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				3, 0, 0, 0, 0, 0, 0,
			},
			guiIndex: 34,
			expect:   false,
		},
	} {
		if actually := IsHunYiSe(unit.cards, unit.guiIndex); actually != unit.expect {
			t.Errorf("IsHunYiSe err, unit:[%v],actually:[%v]\n", unit, actually)
		}
	}
}

func Test_IsYiTiaoLong(t *testing.T) {
	for _, unit := range []struct {
		cards    []int
		guiIndex int
		expect   bool
	}{
		{
			cards: []int{
				3, 1, 1, 1, 1, 1, 1, 1, 1,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 1, 2,
			},
			guiIndex: 33,
			expect:   true,
		},

		{
			cards: []int{
				4, 1, 1, 1, 1, 1, 1, 1, 1,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 2,
			},
			guiIndex: 34,
			expect:   true,
		},

		{
			cards: []int{
				0, 1, 0, 1, 0, 1, 1, 1, 1,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 2, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 3,
			},
			guiIndex: 33,
			expect:   true,
		},

		{
			cards: []int{
				0, 0, 2, 0, 0, 0, 0, 0, 0,
				0, 1, 0, 1, 0, 1, 1, 1, 1,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 3,
			},
			guiIndex: 34,
			expect:   false,
		},

		{
			cards: []int{
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 1, 0, 1, 0, 1, 1, 1, 1,
				0, 0, 1, 1, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 3,
			},
			guiIndex: 33,
			expect:   false,
		},

		{
			cards: []int{
				2, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 3, 0, 0, 0,
			},
			guiIndex: 0,
			expect:   false,
		},
	} {
		if actually := IsYiTiaoLong(unit.cards, unit.guiIndex); actually != unit.expect {
			t.Errorf("IsYiTiaoLong err, unit:[%v],actually:[%v]\n", unit, actually)
		}
	}
}

