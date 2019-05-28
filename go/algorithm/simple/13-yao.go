package simple

func Is_13_yao(cardsIndex []int, gui_index int) bool {

	tmp, gui_num := remove_gui(cardsIndex, gui_index)

	sum := 0
	need := 0
	eye := false
	for _, i := range SHISANYAO_CARDS {
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
