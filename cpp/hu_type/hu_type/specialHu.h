#include "hu_type.h"

int GetGuiNumAndRemoveGui(unsigned char tmpIndex[], unsigned char gui_index = 34);
void AddWeaveToCardIndex(unsigned char tmpIndex[], const tagWeaveItem WeaveItem[], int cbItemCount, int spicalTbl[], int spicalSize);
int MinusWeaveToCardIndex(unsigned char tmpIndex[], const tagWeaveItem WeaveItem[], int cbItemCount, int spicalTbl[], int spicalSize);
bool IsXiaoSanYuan(const unsigned char cbCardIndex[], const tagWeaveItem WeaveItem[], unsigned char cbItemCount, unsigned char gui_index = 34);
bool IsDaSanYuan(const unsigned char cbCardIndex[], const tagWeaveItem WeaveItem[], unsigned char cbItemCount, unsigned char gui_index = 34);
bool IsXiaoSiXi(const unsigned char cbCardIndex[], const tagWeaveItem WeaveItem[], unsigned char cbItemCount, unsigned char gui_index = 34);
bool IsDaSiXi(const unsigned char cbCardIndex[], const tagWeaveItem WeaveItem[], unsigned char cbItemCount, unsigned char gui_index = 34);

inline void PRINT_CARDS(unsigned char allCards[], int allCount)
{
	int cc = 1;
	for (int i = 0; i < allCount; i++)
	{
		printf("%3d", allCards[i]);
		if (cc++ % 9 == 0)
			putchar(10);
	}
	putchar(10);
	cout << "--------------------" << endl
		 << endl;
}

int GetGuiNumAndRemoveGui(unsigned char tmpIndex[], unsigned char gui_index)
{
	int gui_num = 0;
	if (gui_index >= 0 && gui_index < 34)
	{
		gui_num = tmpIndex[gui_index];
		tmpIndex[gui_index] = 0;
	}
	return gui_num;
}

void AddWeaveToCardIndex(unsigned char tmpIndex[], const tagWeaveItem WeaveItem[], int cbItemCount, int spicalTbl[], int spicalSize)
{

	for (int i = 0; i < cbItemCount; i++)
	{
		auto type = WeaveItem[i].cbWeaveKind;
		if (type & (WIK_AN_GANG | WIK_BU_GANG | WIK_MING_GANG | WIK_PENG))
		{
			auto card = WeaveItem[i].cbCenterCard;
			auto index = ((card & 0xf0) >> 4) * 9 + (card & 0x0f) - 1;
			if (index >= spicalTbl[0] && index <= spicalTbl[spicalSize - 1])
			{
				tmpIndex[index] += 3;
			}
		}
	}
}

int MinusWeaveToCardIndex(unsigned char tmpIndex[], const tagWeaveItem WeaveItem[], int cbItemCount, int spicalTbl[], int spicalSize)
{
	int need = 0;
	AddWeaveToCardIndex(tmpIndex, WeaveItem, cbItemCount, spicalTbl, spicalSize);
	for (int i = 0; i < spicalSize; i++)
	{
		auto index = spicalTbl[i];

		if (tmpIndex[index] <= 3)
		{
			need += 3 - tmpIndex[index];
			tmpIndex[index] = 0;
		}
		else
			tmpIndex[index] -= 3;
	}
	return need;
}

// 14 = 5 + 9 (9=3+3+3)
bool IsDaSanYuan(const unsigned char cbCardIndex[], const tagWeaveItem WeaveItem[], unsigned char cbItemCount, unsigned char gui_index)
{

	if (hu_type::check_hu(cbCardIndex, gui_index) == false)
		return false;

	int SANYUAN_CARDS[] = {31, 32, 33};
	int SANYUAN_CARDS_SIZE = sizeof(SANYUAN_CARDS) / sizeof(int);
	unsigned char tmpIndex[34] = {0};
	memcpy(tmpIndex, cbCardIndex, sizeof(tmpIndex));

	int gui_num = GetGuiNumAndRemoveGui(tmpIndex, gui_index);
	int need = MinusWeaveToCardIndex(tmpIndex, WeaveItem, cbItemCount, SANYUAN_CARDS, SANYUAN_CARDS_SIZE);

	if (gui_num - need < 0)
		return false;

	if (gui_index >= 0 && gui_index < 34)
		tmpIndex[gui_index] = gui_num - need;

	return hu_type::check_hu(tmpIndex, gui_index);
}

// 14 = 6 + 8 (8=3+3+2)
bool IsXiaoSanYuan(const unsigned char cbCardIndex[], const tagWeaveItem WeaveItem[], unsigned char cbItemCount, unsigned char gui_index)
{

	if (hu_type::check_hu(cbCardIndex, gui_index) == false)
		return false;

	int SANYUAN_CARDS[] = {31, 32, 33};
	int SANYUAN_CARDS_SIZE = sizeof(SANYUAN_CARDS) / sizeof(int);
	for (int eye = 0; eye < SANYUAN_CARDS_SIZE; eye++)
	{
		int need = 0;
		unsigned char tmpIndex[34];
		memcpy(tmpIndex, cbCardIndex, sizeof(tmpIndex));
		int gui_num = GetGuiNumAndRemoveGui(tmpIndex, gui_index);

		AddWeaveToCardIndex(tmpIndex, WeaveItem, cbItemCount, SANYUAN_CARDS, SANYUAN_CARDS_SIZE);

		if (tmpIndex[SANYUAN_CARDS[eye]] <= 2)
			need = 2 - tmpIndex[SANYUAN_CARDS[eye]];
		else
			need = 3 - (tmpIndex[SANYUAN_CARDS[eye]] - 2);
		tmpIndex[SANYUAN_CARDS[eye]] = 2;

		for (int other = 0; other < SANYUAN_CARDS_SIZE; other++)
		{
			if (other == eye)
				continue;
			if (tmpIndex[SANYUAN_CARDS[other]] <= 3)
				need += 3 - tmpIndex[SANYUAN_CARDS[other]];
			else
				need += 2;
			tmpIndex[SANYUAN_CARDS[other]] = 0;
		}

		if (need > gui_num)
			continue;

		if (gui_index >= 0 && gui_index < 34)
			tmpIndex[gui_index] = gui_num - need;
		if (hu_type::check_hu(tmpIndex, gui_index))
			return true;
	}
	return false;
}

// 14 = 2 + 12 (12=3+3+3+3)
bool IsDaSiXi(const unsigned char cbCardIndex[], const tagWeaveItem WeaveItem[], unsigned char cbItemCount, unsigned char gui_index)
{

	if (hu_type::check_hu(cbCardIndex, gui_index) == false)
		return false;

	int SIXI_CARDS[] = {27, 28, 29, 30};
	int SIXI_CARDS_SIZE = sizeof(SIXI_CARDS) / sizeof(int);
	unsigned char tmpIndex[34];
	memcpy(tmpIndex, cbCardIndex, sizeof(tmpIndex));

	int gui_num = GetGuiNumAndRemoveGui(tmpIndex, gui_index);
	int need = MinusWeaveToCardIndex(tmpIndex, WeaveItem, cbItemCount, SIXI_CARDS, SIXI_CARDS_SIZE);

	if (gui_num - need < 0)
		return false;

	if (gui_index >= 0 && gui_index < 34)
		tmpIndex[gui_index] = gui_num - need;

	return hu_type::check_hu(tmpIndex, gui_index);
}

// 14 = 3 + 11 (11=3+3+3+2)
bool IsXiaoSiXi(const unsigned char cbCardIndex[], const tagWeaveItem WeaveItem[], unsigned char cbItemCount, unsigned char gui_index)
{

	if (hu_type::check_hu(cbCardIndex, gui_index) == false)
		return false;

	int SIXI_CARDS[] = {27, 28, 29, 30};
	int SIXI_CARDS_SIZE = sizeof(SIXI_CARDS) / sizeof(int);
	for (int eye = 0; eye < SIXI_CARDS_SIZE; eye++)
	{
		int need = 0;
		unsigned char tmpIndex[34];
		memcpy(tmpIndex, cbCardIndex, sizeof(tmpIndex));
		int gui_num = GetGuiNumAndRemoveGui(tmpIndex, gui_index);

		AddWeaveToCardIndex(tmpIndex, WeaveItem, cbItemCount, SIXI_CARDS, SIXI_CARDS_SIZE);

		if (tmpIndex[SIXI_CARDS[eye]] <= 2)
			need = 2 - tmpIndex[SIXI_CARDS[eye]];
		else
			need = 3 - (tmpIndex[SIXI_CARDS[eye]] - 2);
		tmpIndex[SIXI_CARDS[eye]] = 2;

		for (int other = 0; other < SIXI_CARDS_SIZE; other++)
		{
			if (other == eye)
				continue;
			if (tmpIndex[SIXI_CARDS[other]] <= 3)
				need += 3 - tmpIndex[SIXI_CARDS[other]];
			else
				need += 2;
			tmpIndex[SIXI_CARDS[other]] = 0;
		}

		if (need > gui_num)
			continue;

		if (gui_index >= 0 && gui_index < 34)
			tmpIndex[gui_index] = gui_num - need;
		if (hu_type::check_hu(tmpIndex, gui_index))
			return true;
	}
	return false;
}

void IsDaSanYuan_test(){

	unsigned char cards[] = {
		2, 1, 3, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 3, 3, 2,
	};

	unsigned char cards1[] = {
		2, 0, 1, 1, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 3, 3, 3,
	};

	unsigned char cards2[] = {
		0, 0, 1, 1, 1, 0, 0, 0, 0,
		2, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 3, 3, 3,
	};

	unsigned char cards3[] = {
		2, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		2, 0, 0, 0, 3, 2, 2,
	};

	unsigned char cards4[] = {
		2, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 3, 0, 0, 4, 3, 2,
	};

	unsigned char cards5[] = {
		3, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 1, 1, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 3, 4, 2,
	};
	unsigned char cards6[] = {
		3, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 2, 0, 0, 4, 3, 2,
	};
	unsigned char cards7[] = {
		4, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		3, 0, 0, 0, 0, 4, 3,
	};

	unsigned char cards8[] = {
		3, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		2, 0, 0, 0, 3, 0, 3,
	};

	unsigned char cards9[] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 1, 1, 1, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		2, 0, 0, 0, 3, 3, 3,
	};

	unsigned char gui_index = 0;
	cout << "cards  -> IsDaSanYuan : " << IsDaSanYuan(cards, NULL, 0, gui_index) << endl;
	cout << "cards1 -> IsDaSanYuan : " << IsDaSanYuan(cards1, NULL, 0, gui_index) << endl;
	cout << "cards2 -> IsDaSanYuan : " << IsDaSanYuan(cards2, NULL, 0, gui_index) << endl;
	cout << "cards3 -> IsDaSanYuan : " << IsDaSanYuan(cards3, NULL, 0, gui_index) << endl;
	cout << "cards4 -> IsDaSanYuan : " << IsDaSanYuan(cards4, NULL, 0, gui_index) << endl;
	cout << "cards5 -> IsDaSanYuan : " << IsDaSanYuan(cards5, NULL, 0, gui_index) << endl;
	cout << "cards6 -> IsDaSanYuan : " << IsDaSanYuan(cards6, NULL, 0, gui_index) << endl;
	cout << "cards7 -> IsDaSanYuan : " << IsDaSanYuan(cards7, NULL, 0, gui_index) << endl;
	cout << "cards8 -> IsDaSanYuan : " << IsDaSanYuan(cards8, NULL, 0, gui_index) << endl;
	cout << "cards9 -> IsDaSanYuan : " << IsDaSanYuan(cards9, NULL, 0, gui_index) << endl;
}

void IsXiaoSanYuan_test(){
	
	unsigned char cards[] = {
		2, 1, 1, 0, 0, 0, 0, 3, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 3, 3, 1,
	};

	unsigned char cards1[] = {
		2, 0, 1, 1, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 3, 3, 3,
	};

	unsigned char cards2[] = {
		0, 0, 1, 1, 1, 0, 0, 0, 0,
		2, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 3, 3, 3,
	};

	unsigned char cards3[] = {
		3, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		3, 0, 0, 0, 4, 2, 2,
	};

	unsigned char cards4[] = {
		2, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		3, 2, 0, 0, 3, 2, 2,
	};

	unsigned char cards5[] = {
		4, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 1, 1, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		3, 0, 0, 0, 3, 0, 2,
	};
	unsigned char cards6[] = {
		4, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 4, 4, 2,
	};
	unsigned char cards7[] = {
		4, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		3, 0, 0, 0, 0, 4, 2,
	};

	unsigned char cards8[] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		3, 0, 0, 0, 3, 2, 3,
	};

	unsigned char cards9[] = {
		2, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		3, 0, 0, 0, 2, 2, 2,
	};

	unsigned char gui_index = 0;
	cout << "cards  -> IsXiaoSanYuan : " << IsXiaoSanYuan(cards,  NULL, 0, gui_index) << endl;
	cout << "cards1 -> IsXiaoSanYuan : " << IsXiaoSanYuan(cards1, NULL, 0, gui_index) << endl;
	cout << "cards2 -> IsXiaoSanYuan : " << IsXiaoSanYuan(cards2, NULL, 0, gui_index) << endl;
	cout << "cards3 -> IsXiaoSanYuan : " << IsXiaoSanYuan(cards3, NULL, 0, gui_index) << endl;
	cout << "cards4 -> IsXiaoSanYuan : " << IsXiaoSanYuan(cards4, NULL, 0, gui_index) << endl;
	cout << "cards5 -> IsXiaoSanYuan : " << IsXiaoSanYuan(cards5, NULL, 0, gui_index) << endl;
	cout << "cards6 -> IsXiaoSanYuan : " << IsXiaoSanYuan(cards6, NULL, 0, gui_index) << endl;
	cout << "cards7 -> IsXiaoSanYuan : " << IsXiaoSanYuan(cards7, NULL, 0, gui_index) << endl;
	cout << "cards8 -> IsXiaoSanYuan : " << IsXiaoSanYuan(cards8, NULL, 0, gui_index) << endl;
	cout << "cards9 -> IsXiaoSanYuan : " << IsXiaoSanYuan(cards9, NULL, 0, gui_index) << endl;
}

void IsDaSiXi_test(){

	unsigned char cards[] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		3, 3, 3, 3, 0, 0, 2,
	};

	unsigned char cards1[] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		4, 3, 3, 2, 0, 0, 2,
	};

	unsigned char cards2[] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 1, 0, 0,
		4, 3, 3, 3, 0, 0, 0,
	};

	unsigned char cards3[] = {
		4, 0, 2, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		2, 2, 2, 2, 0, 0, 0,
	};

	unsigned char cards4[] = {
		3, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 1, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		3, 3, 2, 2, 0, 0, 0,
	};

	unsigned char cards5[] = {
		3, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		3, 4, 2, 2, 0, 0, 0, 
	};
	unsigned char cards6[] = {
		4, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		3, 1, 1, 3, 0, 0, 2,
	};
	unsigned char cards7[] = {
		4, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		3, 3, 3, 1, 0, 0, 0,
	};

	unsigned char cards8[] = {
		4, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		3, 1, 1, 3, 0, 0, 2,
	};

	unsigned char cards9[] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 1, 0, 0, 0, 0, 0,
		3, 3, 3, 4, 0, 0, 0,
	};

	unsigned char gui_index = 0;
	cout << "cards  -> IsDaSiXi : " << IsDaSiXi(cards, NULL, 0, 33) << endl;
	cout << "cards1 -> IsDaSiXi : " << IsDaSiXi(cards1, NULL, 0, 33) << endl;
	cout << "cards2 -> IsDaSiXi : " << IsDaSiXi(cards2, NULL, 0, 27) << endl;
	cout << "cards3 -> IsDaSiXi : " << IsDaSiXi(cards3, NULL, 0, 0) << endl;
	cout << "cards4 -> IsDaSiXi : " << IsDaSiXi(cards4, NULL, 0, 0) << endl;
	cout << "cards5 -> IsDaSiXi : " << IsDaSiXi(cards5, NULL, 0, 0) << endl;
	cout << "cards6 -> IsDaSiXi : " << IsDaSiXi(cards6, NULL, 0, 0) << endl;
	cout << "cards7 -> IsDaSiXi : " << IsDaSiXi(cards7, NULL, 0, 0) << endl;
	cout << "cards8 -> IsDaSiXi : " << IsDaSiXi(cards8, NULL, 0, 0) << endl;
	cout << "cards9 -> IsDaSiXi : " << IsDaSiXi(cards9, NULL, 0, 30) << endl;
}