package simple

func Is_7dui(cardsIndex []int, gui_index int) bool {

	sum := 0
	need := 0
	tmp, gui_num := remove_gui(cardsIndex, gui_index)

	for i := 0; i < MAX_CARD; i++ {
		c := tmp[i]
		sum += c
		if (c > 0) && (c%2 != 0) {
			need++
		}
	}
	return (sum+gui_num == 14) && (gui_num >= need)
}

func Is_haohua_7dui(cardsIndex []int, gui_index int) bool {

	tmp, gui_num := remove_gui(cardsIndex, gui_index)

	lave := gui_num
	sum, dui, need, haohua := 0, 0, 0, 0

	for i := 0; i < MAX_CARD; i++ {
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

	return (sum+gui_num == 14) && (gui_num >= need) && (haohua > 0)
}
