package hulib

func copyAndRemoveGui(cardsIndex []int, gui_index int) ([]int, int) {
	tmp := make([]int, len(cardsIndex))
	copy(tmp, cardsIndex)

	gui_num := 0
	if gui_index != 34 {
		gui_num = tmp[gui_index]
		tmp[gui_index] = 0
	}

	return tmp, gui_num
}

func Is_13_19(cardsIndex []int, gui_index int) bool {

	tmp, gui_num := copyAndRemoveGui(cardsIndex, gui_index)

	sum := 0
	need := 0
	eye := false
	_SHISANYAO_CARDS := []int{0, 8, 9, 17, 18, 26, 27, 28, 29, 30, 31, 32, 33}
	for _, i := range _SHISANYAO_CARDS {
		c := tmp[i]
		if c != 0 {
			if c > 2 {
				return false
			} else if c == 2 {
				if eye {
					return false
				} else {
					eye = true
				}
			}
			sum = sum + c
		} else {
			need++
		}
	}

	if eye {
		return (need == gui_num) && (sum+gui_num == 14)
	} else {
		return (need+1 == gui_num) && (sum+gui_num == 14)
	}
}

func IsXiaoQiDui(cardsIndex []int, gui_index int) (bool, int) {

	tmp, gui_num := copyAndRemoveGui(cardsIndex, gui_index)

	sum := 0
	dui := 0
	need := 0
	lave := gui_num
	haohua := 0

	for i := 0; i < 34; i++ {
		c := tmp[i]
		if c != 0 {
			sum += c
			if c <= 2 {
				dui = dui + 1
				lave = lave - (2 - c)
				need = need + (2 - c)
			} else {
				haohua = haohua + 1
				lave = lave - (4 - c)
				need = need + (4 - c)
			}
		}
	}

	if lave/2 >= dui && lave >= 0 {
		haohua = haohua + dui + (lave/2-dui)/2
	} else if lave/2 < dui && lave >= 0 {
		haohua = haohua + lave/2
	}

	return (sum+gui_num == 14) && (gui_num >= need), haohua
}
