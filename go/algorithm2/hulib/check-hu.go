package hulib

func CheckHu(cardsIndex []int, gui_index int) bool {

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
	need_sum := cache[0] + cache[1] + cache[2] + cache[3]
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
			return check_color(cards[:], eye_color*9, gui_num-(need_sum-cache[eye_color]))
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
			hu = check_color(cards[:], i*9, gui_num-(need_sum-cache[i]))
		}
		if hu {
			return true
		}
	}
	return hu
}

func check_color(cards []int, from int, gui_num int) bool {
	var eye_num int
	var eye_tbl [9]int

	for i := from; i < from+9; i++ {
		if cards[i] > 0 && cards[i]+gui_num >= 2 {
			eye_tbl[eye_num] = i
			eye_num = eye_num + 1
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

func check_normal(cards []int, from int, max_gui int, used_gui int) int {
	var index int
	var cards_tmp [14]int
	var n int
	for i := from; i <= from+8; i++ {
		n = n*10 + cards[i]
		cards_tmp[index] = cards[i]
		index = index + 1
	}

	if n == 0 {
		return 0
	}

	return next_split(cards_tmp[:], 0, max_gui, used_gui)
}

func next_split(cards []int, need_gui int, max_gui int, used_gui int) int {
	index := 0
	for index < 9 {
		c := cards[index]
		index = index + 1
		if c == 0 {
			continue
		}

		if c == 1 || c == 4 {
			one(cards[:], &index, &need_gui, max_gui, used_gui)
		} else if c == 2 {
			two(cards[:], &index, &need_gui, max_gui, used_gui)
		}
	}
	return need_gui
}

func one(cards []int, index *int, need_gui *int, max_gui int, used_gui int) {
	c1 := cards[*index]
	c2 := cards[*index+1]

	if c1 == 0 {
		*need_gui = *need_gui + 1
	} else {
		cards[*index] = cards[*index] - 1
	}

	if c2 == 0 {
		*need_gui = *need_gui + 1
	} else {
		cards[*index+1] = cards[*index+1] - 1
	}

	if *need_gui+used_gui > max_gui+1 {
		*index = 9
		*need_gui = 1000
	}
}

func two(cards []int, index *int, need_gui *int, max_gui int, used_gui int) {
	c1 := cards[*index]
	c2 := cards[*index+1]
	c3 := cards[*index+2]
	c4 := cards[*index+3]
	c5 := cards[*index+4]

	choose_ke := true
	if c1 == 0 {

	} else if c1 == 1 {
		if c2 == 0 || c2 == 1 {

		} else if c2 == 2 {
			if c3 == 2 {
				if c4 == 2 {
					if c5 == 1 || c5 == 4 {
						choose_ke = true
					} else {
						choose_ke = false
					}
				}
			} else if c3 == 3 {
				if c4 != 2 {
					choose_ke = false
				}
			} else {
				choose_ke = false
			}
		} else if c2 == 3 {
			if c3 == 0 || c3 == 2 || c3 == 1 || c3 == 4 {
				choose_ke = false
			}
		} else if c2 == 4 {
			if c3 == 2 {
				if c4 == 2 || c4 == 3 || c4 == 4 {
					choose_ke = false
				}
			} else if c3 == 3 {
				choose_ke = false
			}
		}
	} else if c1 == 2 {
		choose_ke = false
	} else if c1 == 3 {
		if c2 == 2 {
			if c3 == 1 || c3 == 4 {
				choose_ke = false
			} else if c3 == 2 {
				if c4 != 2 {
					choose_ke = false
				}
			}
		} else if c2 == 3 {
			choose_ke = false
		} else if c2 == 4 {
			if c3 == 2 {
				choose_ke = false
			}
		}
	} else if c1 == 4 {
		if c2 == 2 && c3 != 2 {
			choose_ke = false
		} else if c2 == 3 {
			if c3 == 0 || c3 == 1 || c3 == 2 {
				choose_ke = false
			}
		} else if c2 == 4 {
			if c3 == 2 {
				choose_ke = false
			}
		}
	}

	if choose_ke {
		*need_gui += 1
	} else {
		if c1 < 2 {
			*need_gui += (2 - c1)
			cards[*index] -= c1
		} else {
			cards[*index] -= 2
		}

		if c2 < 2 {
			*need_gui += (2 - c2)
			cards[*index+1] -= c2
		} else {
			cards[*index+1] -= 2
		}
	}

	if *need_gui+used_gui > max_gui+1 {
		*index = 9
	}
}

func check_zi(cards []int) int {
	need_gui := 0
	for i := 27; i < 34; i++ {
		if cards[i] == 0 {
			continue
		}

		if cards[i] == 1 || cards[i] == 4 {
			need_gui = need_gui + 2
		} else if cards[i] == 2 {
			need_gui = need_gui + 1
		}
	}
	return need_gui
}
