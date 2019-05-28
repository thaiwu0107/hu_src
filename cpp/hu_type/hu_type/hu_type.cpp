
#include "hu_type.h"

int hu_type::m_haohuaNum = 0;

inline unsigned char ConverseToIndex(unsigned char cbCardData)
{
	return ((cbCardData & 0xf0) >> 4) * 9 + (cbCardData & 0x0f) - 1;
}

bool hu_type::Is_13_19(const unsigned char cbCardIndex[], unsigned char gui_index)
{
	int gui_num = 0;
	unsigned char cards_dict[34];
	memcpy(cards_dict, cbCardIndex, sizeof(cards_dict));
	if (gui_index != 34)
	{
		gui_num = cbCardIndex[gui_index];
		cards_dict[gui_index] = 0;
	}

	int sum = 0;
	int need = 0;
	bool eye = false;
	unsigned char SHISANYAO_CARDS[] = { 0, 8, 9, 17, 18, 26, 27, 28, 29, 30, 31, 32, 33 };

	for (int i = 0; i < sizeof(SHISANYAO_CARDS); i++)
	{
		int c = cards_dict[SHISANYAO_CARDS[i]];
		if (c != 0)
		{
			if (c > 2)
				return false;
			else if (c == 2)
			{
				if (eye)
					return false;
				else
					eye = true;
			}
			sum = sum + c;
		}
		else
			need++;
	}

	if (eye)
		return (need == gui_num) && (sum + gui_num == 14);
	else
		return (need + 1 == gui_num) && (sum + gui_num == 14);
}

bool hu_type::IsQiXiaoDui(const unsigned char cbCardIndex[], unsigned char gui_index)
{
	m_haohuaNum = 0;
	int gui_num = 0;
	unsigned char cards_dict[34];
	memcpy(cards_dict, cbCardIndex, sizeof(cards_dict));
	if (gui_index != 34)
	{
		gui_num = cbCardIndex[gui_index];
		cards_dict[gui_index] = 0;
	}

	int sum = 0;
	int dui = 0;
	int need_gui = 0;
	int haohua = 0;
	int lave = gui_num;
	for (int i = 0; i < 34; i++)
	{
		int c = cards_dict[i];
		if (c > 0)
		{
			sum = sum + c;
			if (c <= 2)
			{
				dui = dui + 1;
				lave = lave - (2 - c);
				need_gui = need_gui + (2 - c);
			}
			else
			{
				haohua = haohua + 1;
				lave = lave - (4 - c);
				need_gui = need_gui + (4 - c);
			}
		}
	}

	if (lave / 2 >= dui && lave >= 0)
		haohua = haohua + dui + (lave / 2 - dui) / 2;
	else if (lave / 2 < dui && lave >= 0)
		haohua = haohua + lave / 2;
	m_haohuaNum = haohua;
	return (sum + gui_num == 14) && (gui_num >= need_gui);
}

bool hu_type::IsPengPeng(const unsigned char cbCardIndex[], const tagWeaveItem WeaveItem[], unsigned char cbItemCount, unsigned char gui_index)
{
	for (unsigned char i = 0; i < cbItemCount; i++)
	{
		auto type = WeaveItem[i].cbWeaveKind;
		if ((type == WIK_LEFT) || (type == WIK_CENTER) || (type == WIK_RIGHT))
			return false;
	}

	int need = 0;
	int gui_num = 0;
	unsigned char cards_dict[34];
	memcpy(cards_dict, cbCardIndex, sizeof(cards_dict));
	if (gui_index != 34)
	{
		gui_num = cbCardIndex[gui_index];
		cards_dict[gui_index] = 0;
	}

	for (int i = 0; i < 34; i++)
	{
		int c = cards_dict[i];
		if (c == 0)
			continue;
		else if (c > 0 && c < 4)
			need = need + 3 - c;
		else if (c == 4)
			need = need + 2;
	}
	if ((gui_num - need - 2 >= 0) || (gui_num - need + 1 >= 0))
		return ((gui_num - need - 2) % 3 == 0 || (gui_num - need + 1) % 3 == 0);
	return false;
}

bool hu_type::IsQingYiSe(const unsigned char cbCardIndex[], const tagWeaveItem WeaveItem[], const unsigned char cbItemCount, unsigned char gui_index)
{
	unsigned char cards_dict[34];
	memcpy(cards_dict, cbCardIndex, sizeof(cards_dict));
	if (gui_index != 34)
		cards_dict[gui_index] = 0;

	int colors[4] = { 0, 0, 0, 0 };
	for (int i = 0; i < 34; i++)
	{
		if (cards_dict[i] > 0)
		{
			int color = floor(i / 9);
			colors[color] = 1;
		}
	}

	for (int i = 0; i < cbItemCount; i++)
	{
		int card = WeaveItem[i].cbCenterCard;
		int color = (card & 0xf0) >> 4;
		colors[color] = 1;
	}
	return (colors[0] + colors[1] + colors[2] == 1) && colors[3] == 0;
}

bool hu_type::IsHunYiSe(const unsigned char cbCardIndex[], const tagWeaveItem WeaveItem[], const unsigned char cbItemCount, unsigned char gui_index)
{
	unsigned char cards_dict[34];
	memcpy(cards_dict, cbCardIndex, sizeof(cards_dict));
	if (gui_index != 34)
		cards_dict[gui_index] = 0;

	int colors[4] = { 0, 0, 0, 0 };
	for (int i = 0; i < 34; i++)
	{
		if (cards_dict[i] > 0)
		{
			int color = floor(i / 9);
			colors[color] = 1;
		}
	}

	for (int i = 0; i < cbItemCount; i++)
	{
		int card = WeaveItem[i].cbCenterCard;
		int color = (card & 0xf0) >> 4;
		colors[color] = 1;
	}
	return (colors[0] + colors[1] + colors[2] == 1) && colors[3] == 1;
}

bool hu_type::IsZiYiSe(const unsigned char cbCardIndex[], const tagWeaveItem WeaveItem[], const unsigned char cbItemCount, unsigned char gui_index)
{
	unsigned char cards_dict[34];
	memcpy(cards_dict, cbCardIndex, sizeof(cards_dict));
	if (gui_index != 34)
		cards_dict[gui_index] = 0;

	int colors[4] = { 0, 0, 0, 0 };
	for (int i = 0; i < 34; i++)
	{
		if (cards_dict[i] > 0)
		{
			int color = floor(i / 9);
			colors[color] = 1;
		}
	}

	for (int i = 0; i < cbItemCount; i++)
	{
		int card = WeaveItem[i].cbCenterCard;
		int color = (card & 0xf0) >> 4;
		colors[color] = 1;
	}
	return (colors[0] + colors[1] + colors[2] == 0) && colors[3] == 1;
}

bool hu_type::IsYiTiaoLong(const unsigned char cbCardIndex[], unsigned char gui_index)
{
	bool hu = false;

	for (int color = 0; color < 3; color++)
	{
		int need = 0;
		int gui_num = 0;
		unsigned char cards_dict[34];
		memcpy(cards_dict, cbCardIndex, sizeof(cards_dict));
		if (gui_index != 34)
		{
			gui_num = cards_dict[gui_index];
			cards_dict[gui_index] = 0;
		}

		for (int card = 0 + 9 * color; card < 9 + 9 * color; card++)
		{
			if (cards_dict[card] == 0)
				need++;
			else
				cards_dict[card]--;
		}
		if (gui_num - need >= 0)
		{
			cards_dict[gui_index] = gui_num - need;
			if (hu_type::check_hu(cards_dict, gui_index))
			{
				hu = true;
				break;
			}
		}
		continue;
	}
	return hu;
}

bool hu_type::IsKaZhang(const unsigned char cbCardIndex[], unsigned char targetCard, unsigned char gui_index)
{
	if (cbCardIndex[ConverseToIndex(targetCard)] <= 0)
		return false;
	int flag = 0;
	int hu_num = 0;
	bool hu_flag = 0;
	unsigned char cards_dict[34];
	memcpy(cards_dict, cbCardIndex, sizeof(cards_dict));
	cards_dict[ConverseToIndex(targetCard)]--;

	for (int i = 0; i < 34; i++)
	{
		cards_dict[i]++;
		hu_flag = hu_type::check_hu(cards_dict, gui_index);
		if (hu_flag)
		{
			if (i == gui_index)
				flag = 1;
			hu_num++;
		}
		cards_dict[i]--;
	}
	return hu_num == 1 + flag;
}

bool hu_type::IsShunZiHu(const unsigned char cbCardIndex[], unsigned char temp_gui_index)
{
	char cards[34];
	char gui_index;
	memcpy(cards, cbCardIndex, sizeof(cards));
	gui_index = temp_gui_index;

	char gui_num = 0;
	if (gui_index != 34)
	{
		gui_num = cards[gui_index];
		cards[gui_index] = 0;
	}

	//eye
	char eye_tbl[34];
	char eye_num = 0;
	char empty = -1;

	int count = 0;
	for (int i = 27; i < 34; i++)
	{
		if (cards[i] != 0)
			++count;
		if (count >= 2 || cards[i] >= 3)
			return false;
		if (cards[i] > 0 && cards[i] + gui_num >= 2)
			eye_tbl[eye_num++] = i;
	}

	if (count == 0)
	{
		for (int i = 0; i < 27; i++)
		{
			if (cards[i] > 0 && cards[i] + gui_num >= 2)
				eye_tbl[eye_num++] = i;
		}
	}

	if (gui_num >= 2)
	{
		eye_tbl[eye_num++] = empty;
	}

	bool hu = false;
	for (int i = 0; i < eye_num; i++)
	{
		int eye = eye_tbl[i];
		if (eye == empty)
			hu = check_foreach_eye(cards, gui_num - 2);
		else
		{
			char n = cards[eye];
			if (n == 1)
			{
				cards[eye] = 0;
				hu = check_foreach_eye(cards, gui_num - 1);
			}
			else
			{
				cards[eye] -= 2;
				hu = check_foreach_eye(cards, gui_num);
			}
			cards[eye] = n;
		}
		if (hu)
			break;
	}

	if (gui_num > 0)
	{
		cards[gui_index] = gui_num;
	}
	return hu;
}

bool hu_type::check_foreach_eye(char *cards, char gui_num)
{
	int left_gui = gui_num;
	for (int i = 0; i < 3; i++)
	{
		int need_gui = check_foreach_color_need(cards, i * 9, i * 9 + 8);
		left_gui = left_gui - need_gui;
		if (left_gui < 0)
		{
			return false;
		}
	}
	return ((left_gui >= 0) && (left_gui % 3 == 0));
}

int hu_type::check_foreach_color_need(char *cards, int from, int to)
{
	int n = 0;
	for (int i = from; i <= to; i++)
		n = n * 10 + cards[i];

	int need = 0;
	if (n != 0)
	{
		int c, c1, c2;

		while (n > 0)
		{
			c = n % 10;
			if (c != 0)
			{
				n = n - c;
				c1 = (n % 100) / 10;
				c2 = (n % 1000) / 100;

				if (c1 <= c)
				{
					need = need + c - c1;
					n = n - c1 * 10;
				}
				else
					n = n - c * 10;

				if (c2 <= c)
				{
					need = need + c - c2;
					n = n - c2 * 100;
				}
				else
					n = n - c * 100;
			}

			if (n == 0)
				break;
			n = n / 10;
		}
	}
	return need;
}

bool hu_type::IsHuaLong(const unsigned char cbCardIndex[], unsigned char gui_index)
{

	int num = 0;
	for (int i = 0; i < 34; i++)
		num += cbCardIndex[i];
	if (num <= 9)
		return false;

	if (!(hu_type::check_hu(cbCardIndex, gui_index)))
		return false;

	for (int c = 0; c < 3; c++)
	{
		for (int c1 = 0; c1 < 3; c1++)
		{
			if (c != c1)
			{

				unsigned char tmpCards[34] = { 0 };
				memcpy(tmpCards, cbCardIndex, 34);

				int Colors[3] = { 0 };
				Colors[0] = c, Colors[1] = c1, Colors[2] = 3 - c - c1;

				int gui_num = 0;
				if (gui_index < 34 && gui_index >= 0)
					gui_num = cbCardIndex[gui_index];

				int need = hu_type::removeAndGetNeed(tmpCards, Colors);

				if (need > gui_num)
					continue;

				if ((gui_index < 34 && gui_index >= 0) && gui_num >= need)
					tmpCards[gui_index] -= need;

				if (hu_type::check_hu(tmpCards, gui_index))
					return true;
			}
		}
	}
	return false;
}

int hu_type::removeAndGetNeed(unsigned char tmpCards[], int Colors[3])
{
	int need = 0;

	for (int i = 0; i < 9; i++)
	{
		int color = i / 3;
		int index = Colors[color] * 9;

		if (tmpCards[index + i] <= 0)
			need++;
		else
			tmpCards[index + i]--;
	}
	return need;
}

//  hu ?
bool hu_type::check_hu(const unsigned char cbCardIndex[], unsigned char temp_gui_index)
{
	char cards[34];
	char gui_index = temp_gui_index;
	int cbCardCount = 0;

	for (int i = 0; i < 34; i++)
	{
		cards[i] = cbCardIndex[i];
		cbCardCount += cbCardIndex[i];
	}

	if (cbCardCount % 3 != 2)
		return false;

	char gui_num = 0;
	if (gui_index < 34 && gui_index >= 0)
	{
		gui_num = cards[gui_index];
		cards[gui_index] = 0;
	}
	int used_gui = 0;
	int cache[] = { 0, 0, 0, 0 };
	int counter[] = { 0, 0, 0, 0 };
	cache[0] = check_normal(cards, 0, gui_num, used_gui);
	used_gui = cache[0];
	if (used_gui > 1 + gui_num)
		return false;

	cache[1] = check_normal(cards, 9, gui_num, used_gui);
	used_gui = cache[0] + cache[1];
	if (used_gui > 1 + gui_num)
		return false;

	cache[2] = check_normal(cards, 18, gui_num, used_gui);
	used_gui = cache[0] + cache[1] + cache[2];
	if (used_gui > 1 + gui_num)
		return false;

	cache[3] = check_zi(cards);
	int need_sum = cache[0] + cache[1] + cache[2] + cache[3];
	if (need_sum > 1 + gui_num)
		return false;

	//printf("----------> need_sum : %d\n", need_sum);
	if (need_sum + 2 <= gui_num)
	{
		return true;
	}

	int eye_color = -1;

	for (int i = 0; i < 4; i++)
	{
		int n = cache[i];
		if (n > gui_num)
		{
			if (eye_color >= 0)
				return false;
			if (need_sum - n > gui_num)
				return false;
			if (need_sum - 1 > gui_num)
				return false;

			eye_color = i;
			break;
		}
	}

	if (eye_color > 0)
	{
		if (eye_color == 3)
		{
			return true;
		}
		else
		{
			return check_color(cards, eye_color * 9, gui_num - (need_sum - cache[eye_color]));
		}
	}

	bool hu = false;
	for (int i = 0; i < 4; ++i)
	{
		if (cache[i] == 0)
			continue;
		if (i == 3)
		{
			return true;
		}
		else
		{
			hu = check_color(cards, i * 9, gui_num - (need_sum - cache[i]));
		}
		if (hu)
			return true;
	}

	return hu;
}

bool hu_type::check_color(char *cards, char from, char gui_num)
{
	char eye_tbl[9];
	char eye_num = 0;
	for (int i = from; i < from + 9; i++)
	{
		if (cards[i] > 0 && cards[i] + gui_num >= 2)
		{
			eye_tbl[eye_num++] = i;
		}
	}

	if (eye_num == 0)
		return false;

	for (int i = 0; i < eye_num; i++)
	{
		int eye = eye_tbl[i];
		char n = cards[eye];
		if (n == 1)
		{
			cards[eye] = 0;
			int need_gui = check_normal(cards, from, gui_num - 1, 0);
			if (need_gui < gui_num)
				return true;
		}
		else
		{
			cards[eye] -= 2;
			int need_gui = check_normal(cards, from, gui_num, 0);
			if (need_gui <= gui_num)
				return true;
		}

		cards[eye] = n;
	}

	return false;
}

int hu_type::check_normal(char *cards, int from, int max_gui, int used_gui)
{
	char index = 0;
	char cards_tmp[14] = { 0 };
	int n = 0;
	for (int i = from; i <= from + 8; i++)
	{

		n = n * 10 + cards[i];
		cards_tmp[index++] = cards[i];
	}

	if (n == 0)
		return 0;

	return next_split(cards_tmp, 0, max_gui, used_gui);
}

int hu_type::next_split(char *cards, int need_gui, int max_gui, int used_gui)
{
	int index = 0;
	while (index < 9)
	{
		int c = cards[index++];
		if (c == 0)
			continue;

		if (c == 1 || c == 4)
		{
			one(cards, index, need_gui, max_gui, used_gui);
		}
		else if (c == 2)
		{
			two(cards, index, need_gui, max_gui, used_gui);
		}
	}
	return need_gui;
}

void hu_type::one(char *cards, int &index, int &need_gui, int max_gui, int used_gui)
{
	int c1 = cards[index];
	int c2 = cards[index + 1];

	if (c1 == 0)
		++need_gui;
	else
		cards[index]--;

	if (c2 == 0)
		++need_gui;
	else
		cards[index + 1]--;

	if (need_gui + used_gui > max_gui + 1)
	{
		index = 9;
		need_gui = 1000;
	}
}

void hu_type::two(char *cards, int &index, int &need_gui, int max_gui, int used_gui)
{
	int c1 = cards[index];
	int c2 = cards[index + 1];
	int c3 = cards[index + 2];
	int c4 = cards[index + 3];
	int c5 = cards[index + 4];

	bool choose_ke = true;
	if (c1 == 0)
	{
	}
	else if (c1 == 1)
	{
		if (c2 == 0 || c2 == 1)
		{
		}
		else if (c2 == 2)
		{
			if (c3 == 2)
			{
				if (c4 == 2)
				{
					if (c5 == 1 || c5 == 4)
						choose_ke = true;
					else
						choose_ke = false;
				}
			}
			else if (c3 == 3)
			{
				if (c4 != 2)
					choose_ke = false;
			}
			else
				choose_ke = false;
		}
		else if (c2 == 3)
		{
			if (c3 == 0 || c3 == 2 || c3 == 1 || c3 == 4)
				choose_ke = false;
		}
		else if (c2 == 4)
		{
			if (c3 == 2)
			{
				if (c4 == 2 || c4 == 3 || c4 == 4)
					choose_ke = false;
			}
			else if (c3 == 3)
			{
				choose_ke = false;
			}
		}
	}
	else if (c1 == 2)
	{
		choose_ke = false;
	}
	else if (c1 == 3)
	{
		if (c2 == 2)
		{
			if (c3 == 1 || c3 == 4)
				choose_ke = false;
			else if (c3 == 2)
			{
				if (c4 != 2)
					choose_ke = false;
			}
		}
		else if (c2 == 3)
			choose_ke = false;
		else if (c2 == 4)
		{
			if (c3 == 2)
				choose_ke = false;
		}
	}
	else if (c1 == 4)
	{
		if (c2 == 2 && c3 != 2)
			choose_ke = false;
		else if (c2 == 3)
		{
			if (c3 == 0 || c3 == 1 || c3 == 2)
				choose_ke = false;
		}
		else if (c2 == 4)
		{
			if (c3 == 2)
				choose_ke = false;
		}
	}

	if (choose_ke)
	{
		need_gui += 1;
	}
	else
	{
		if (c1 < 2)
		{
			need_gui += (2 - c1);
			cards[index] -= c1;
		}
		else
		{
			cards[index] -= 2;
		}

		if (c2 < 2)
		{
			need_gui += (2 - c2);
			cards[index + 1] -= c2;
		}
		else
		{
			cards[index + 1] -= 2;
		}
	}

	if (need_gui + used_gui > max_gui + 1)
	{
		index = 9;
	}
}

int hu_type::check_zi(char *cards)
{
	int need_gui = 0;
	for (int i = 27; i < 34; i++)
	{
		if (cards[i] == 0)
			continue;
		if (cards[i] == 1 || cards[i] == 4)
		{
			need_gui += 2;
		}
		else if (cards[i] == 2)
		{
			++need_gui;
		}
	}

	return need_gui;
}

// hu 258 ?
bool hu_type::check_hu_258(const unsigned char cbCardIndex[], unsigned char temp_gui_index)
{
	char cards[34];
	char gui_index = temp_gui_index;
	int cbCardCount = 0;

	for (int i = 0; i < 34; i++)
	{
		cards[i] = cbCardIndex[i];
		cbCardCount += cbCardIndex[i];
	}

	if (cbCardCount % 3 != 2)
		return false;

	char gui_num = 0;
	if (gui_index != 34)
	{
		gui_num = cards[gui_index];
		cards[gui_index] = 0;
	}
	int used_gui = 0;
	int cache[] = { 0, 0, 0, 0 };
	int counter[] = { 0, 0, 0, 0 };
	cache[0] = check_normal(cards, 0, gui_num, used_gui);
	used_gui = cache[0];
	if (used_gui > 1 + gui_num)
		return false;

	cache[1] = check_normal(cards, 9, gui_num, used_gui);
	used_gui = cache[0] + cache[1];
	if (used_gui > 1 + gui_num)
		return false;

	cache[2] = check_normal(cards, 18, gui_num, used_gui);
	used_gui = cache[0] + cache[1] + cache[2];
	if (used_gui > 1 + gui_num)
		return false;

	cache[3] = check_zi(cards);
	gui_num -= cache[3];
	int need_sum = cache[0] + cache[1] + cache[2];
	if (need_sum > 1 + gui_num)
		return false;

	//printf("----------> need_gui : %d\n", need_sum);
	if (need_sum + 2 <= gui_num)
	{
		return true;
	}

	int eye_color = -1;

	for (int i = 0; i < 4; i++)
	{
		int n = cache[i];
		if (n > gui_num)
		{
			if (eye_color >= 0)
				return false;
			if (need_sum - n > gui_num)
				return false;
			if (need_sum - 1 > gui_num)
				return false;

			eye_color = i;
			break;
		}
	}

	if (eye_color > 0)
	{
		if (eye_color == 3)
		{
			return true;
		}
		else
		{
			return check_color_258(cards, eye_color * 9, gui_num - (need_sum - cache[eye_color]));
		}
	}

	bool hu = false;
	for (int i = 0; i < 4; ++i)
	{
		if (cache[i] == 0)
			continue;
		if (i == 3)
		{
			return true;
		}
		else
		{
			hu = check_color_258(cards, i * 9, gui_num - (need_sum - cache[i]));
		}
		if (hu)
			return true;
	}

	return hu;
}

bool hu_type::check_color_258(char *cards, char from, char gui_num)
{
	char eye_tbl[9];
	char eye_num = 0;
	for (int i = from; i < from + 9; i++)
	{
		if (cards[i] > 0 && cards[i] + gui_num >= 2)
		{
			if (i >= 0 && i < 27)
			{
				int value = i % 9 + 1;
				if (value == 2 || value == 5 || value == 8)
					eye_tbl[eye_num++] = i;
			}
		}
	}

	if (eye_num == 0)
		return false;

	for (int i = 0; i < eye_num; i++)
	{
		int eye = eye_tbl[i];
		char n = cards[eye];
		if (n == 1)
		{
			cards[eye] = 0;
			int need_gui = check_normal(cards, from, gui_num - 1, 0);
			if (need_gui < gui_num)
				return true;
		}
		else
		{
			cards[eye] -= 2;
			int need_gui = check_normal(cards, from, gui_num, 0);
			if (need_gui <= gui_num)
				return true;
		}

		cards[eye] = n;
	}

	return false;
}
