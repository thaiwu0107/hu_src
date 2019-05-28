package hulib

func CheckHu_258(cardsIndex []int, gui_index int) bool {

	var cardsNum int
	for i := 0; i < len(cardsIndex); i++ {
		cardsNum += cardsIndex[i]
	}
	if cardsNum%3 != 2 {
		return false
	}

	gui_num := 0
	cards := make([]int, len(cardsIndex))
	copy(cards, cardsIndex)

	if gui_index < 34 && gui_index >= 0 {
		gui_num = cards[gui_index]
		cards[gui_index] = 0
	}

	used_gui := 0
	cache := []int{0, 0, 0, 0}

	cache[0] = check_normal(cards[:], 0, gui_num, used_gui)
	used_gui = cache[0]
	if used_gui > 1+gui_num {
		return false
	}

	cache[1] = check_normal(cards[:], 9, gui_num, used_gui)
	used_gui = cache[0] + cache[1]
	if used_gui > 1+gui_num {
		return false
	}

	cache[2] = check_normal(cards[:], 18, gui_num, used_gui)
	used_gui = cache[0] + cache[1] + cache[2]
	if used_gui > 1+gui_num {
		return false
	}

	cache[3] = check_zi(cards[:])

	gui_num = gui_num - cache[3]
	need_sum := cache[0] + cache[1] + cache[2]

	if need_sum > 1+gui_num {
		return false
	}

	if need_sum+2 <= gui_num {
		return true
	}

	eye_color := -1

	for i := 0; i < 4; i++ {
		n := cache[i]
		if n > gui_num {
			if eye_color >= 0 {
				return false
			}
			if need_sum-n > gui_num {
				return false
			}
			if need_sum-1 > gui_num {
				return false
			}
			eye_color = i
			break
		}
	}

	if eye_color > 0 {
		if eye_color == 3 {
			return true
		} else {
			return check_color_258(cards[:], eye_color*9, gui_num-(need_sum-cache[eye_color]))
		}
	}

	hu := false
	for i := 0; i < 4; i++ {
		if cache[i] == 0 {
			continue
		}
		if i == 3 {
			return true
		} else {
			hu = check_color_258(cards[:], i*9, gui_num-(need_sum-cache[i]))
		}
		if hu {
			return true
		}
	}
	return hu
}

func check_color_258(cards []int, from int, gui_num int) bool {
	var eye_num int
	var eye_tbl [9]int

	for i := from; i < from+9; i++ {
		if cards[i] > 0 && cards[i]+gui_num >= 2 {
			if i >= 0 && i < 27 {
				value := i%9 + 1
				if value == 2 || value == 5 || value == 8 {
					eye_tbl[eye_num] = i
					eye_num = eye_num + 1
				}

			}
		}
	}

	if eye_num == 0 {
		return false
	}

	for i := 0; i < eye_num; i++ {
		eye := eye_tbl[i]
		n := cards[eye]
		if n == 1 {
			cards[eye] = 0
			need_gui := check_normal(cards[:], from, gui_num-1, 0)
			if need_gui < gui_num {
				return true
			}
		} else {
			cards[eye] -= 2
			need_gui := check_normal(cards[:], from, gui_num, 0)
			if need_gui <= gui_num {
				return true
			}
		}
		cards[eye] = n
	}
	return false
}
