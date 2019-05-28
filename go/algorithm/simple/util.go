package simple

var (
	MAX_CARD        = 34
	SHISANYAO_CARDS = []int{0, 8, 9, 17, 18, 26, 27, 28, 29, 30, 31, 32, 33} //13yao
)

func get_count(cardsIndex []int, gui_index int) int {
	sum := 0
	for i := 0; i < len(cardsIndex); i++ {
		sum += cardsIndex[i]
	}
	return sum
}

func remove_gui(cardsIndex []int, gui_index int) ([]int, int) {
	tmp := make([]int, len(cardsIndex))
	copy(tmp, cardsIndex)

	gui_num := 0
	if gui_index != 34 {
		gui_num = tmp[gui_index]
		tmp[gui_index] = 0
	}

	return tmp, gui_num
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
