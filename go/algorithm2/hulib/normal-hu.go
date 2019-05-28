package hulib

func IsPengPengHu(cardsIndex []int, gui_index int) bool {

	tmp, gui_num := copyAndRemoveGui(cardsIndex, gui_index)
	need := 0
	for i := 0; i < 34; i++ {
		c := tmp[i]
		if c > 0 && c < 4 {
			need = need + 3 - c
		} else if c == 4 {
			need = need + 2
		}
	}
	if (gui_num-need-2 >= 0) || (gui_num-need+1 >= 0) {
		return ((gui_num-need-2)%3 == 0 || (gui_num-need+1)%3 == 0)
	}
	return false
}

func IsKaZhang(cardsIndex []int, targetCard int, gui_index int) bool {
	if cardsIndex[targetCard] <= 0 {
		return false
	}

	flag := 0
	hu_num := 0
	cards_dict := make([]int, 34)
	copy(cards_dict, cardsIndex)
	cards_dict[targetCard]--

	for i := 0; i < 34; i++ {
		cards_dict[i]++
		if CheckHu(cards_dict, gui_index) {
			if i == gui_index {
				flag = 1
			}
			hu_num++
		}
		cards_dict[i]--
	}
	return (hu_num == (1 + flag))
}

func IsYiTiaoLong(cardsIndex []int, gui_index int) bool {
	hu := false

	for color := 0; color < 3; color++ {
		need := 0
		gui_num := 0
		cards_dict := make([]int, 34)
		copy(cards_dict, cardsIndex)
		if gui_index != 34 {
			gui_num = cards_dict[gui_index]
			cards_dict[gui_index] = 0
		}

		for card := 0 + 9*color; card < 9+9*color; card++ {
			if cards_dict[card] == 0 {
				need++
			} else {
				cards_dict[card]--
			}
		}

		if gui_num-need >= 0 {
			if gui_index < 34 && gui_index >= 0 {
				cards_dict[gui_index] = gui_num - need
			}

			if CheckHu(cards_dict, gui_index) {
				hu = true
				break
			}
		}
		continue
	}
	return hu
}

func GetCardsColor(cardsIndex []int, gui_index int) []int {

	tmp := make([]int, len(cardsIndex))
	copy(tmp, cardsIndex)

	colors := []int{0, 0, 0, 0}
	if gui_index != 34 {
		tmp[gui_index] = 0
	}
	for i := 0; i < 34; i++ {
		if tmp[i] > 0 {
			color := i / 9
			colors[color] = 1
		}
	}
	return colors
}

func IsQingYiSe(cardsIndex []int, gui_index int) bool {
	colors := GetCardsColor(cardsIndex, gui_index)
	return ((colors[0]+colors[1]+colors[2] == 1) && colors[3] == 0)
}

func IsHunYiSe(cardsIndex []int, gui_index int) bool {
	colors := GetCardsColor(cardsIndex, gui_index)
	return ((colors[0]+colors[1]+colors[2] == 1) && colors[3] == 1)
}

func IsZiYiSe(cardsIndex []int, gui_index int) bool {
	colors := GetCardsColor(cardsIndex, gui_index)
	return ((colors[0]+colors[1]+colors[2] == 0) && colors[3] == 1)
}
