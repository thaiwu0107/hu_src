
//回溯法
#include <string.h>
#include <iostream>
using namespace std;

bool check_zi_huisu(unsigned char *cards, bool &eye);
bool check_color_huisu(unsigned char *cards, bool &eye);
bool cai_cur(int cur, unsigned char *cards, bool &eye);

struct HUISU_ITEM
{
	unsigned char a;
	unsigned char b;
	unsigned char c;
	bool eye;
};

HUISU_ITEM huisu_items1[] = {
	{1, 1, 1, false},
};

HUISU_ITEM huisu_items2[] = {
	{2, 0, 0, true},
	{2, 2, 2, false},
};

HUISU_ITEM huisu_items3[] = {
	{3, 0, 0, false},
	{3, 1, 1, true},
};

HUISU_ITEM huisu_items4[] = {
	{4, 1, 1, false},
	{4, 2, 2, true},
};

HUISU_ITEM *get_huisu_ops(unsigned char cur_num, int *op_num)
{
	*op_num = 0;
	if (cur_num == 1)
	{
		*op_num = 1;
		return huisu_items1;
	}
	if (cur_num == 2)
	{
		*op_num = 2;
		return huisu_items2;
	}
	if (cur_num == 3)
	{
		*op_num = 2;
		return huisu_items3;
	}
	if (cur_num == 4)
	{
		*op_num = 2;
		return huisu_items4;
	}
}

// 字牌是否满足胡牌条件
bool check_zi_huisu(unsigned char *cards, bool &eye)
{
	for (int i = 27; i < 34; ++i)
	{
		if (cards[i] == 0)
			continue;

		if (cards[i] == 1 || cards[i] == 4)
			return false;

		if (eye && cards[i] == 2)
			return false;

		if (cards[i] == 2)
			eye = true;
	}

	return true;
}

//这里的cards是含有九个元素的数组
bool check_color_huisu(unsigned char *cards, bool &eye)
{
	int sum = 0;
	for (int i = 0; i < 9; i++)
		sum += cards[i];

	if (sum == 0)
		return true;
	int yu = sum % 3;
	if (yu == 1)
		return false;
	if (yu == 2 && eye)
		return false;

	return cai_cur(0, cards, eye);
}

bool cai_cur(int cur, unsigned char *cards, bool &eye)
{
	if (cur > 8)
		return true;

	int n = cards[cur];
	if (n == 0)
		return cai_cur(cur + 1, cards, eye);

	// 获取所有可拆解情况
	int op_num = 0;
	HUISU_ITEM *p = NULL;
	p = get_huisu_ops(n, &op_num);
	for (int i = 0; i < op_num; ++i)
	{
		HUISU_ITEM &pi = p[i];
		if (eye && p[i].eye) continue;
		if (cur + 1 >= 9 && pi.b > 0) continue;
		if (cur + 2 >= 9 && pi.c > 0) continue;
		if (pi.b > 0 && pi.b > cards[cur + 1] || pi.c > 0 && cards[cur + 2] < pi.c)
			continue;

		cards[cur] = 0;
		cards[cur + 1] -= pi.b;
		cards[cur + 2] -= pi.c;
		bool e = eye || pi.eye;
		bool result = cai_cur(cur + 1, cards, e);

		cards[cur] = p[i].a;
		cards[cur + 1] += pi.b;
		cards[cur + 2] += pi.c;
		if (result)
		{
			eye = e;
			return true;
		}
	}
	return false;
}

bool check_hu_huisu(unsigned char *cards)
{
	bool eye = false;

	if (!check_zi_huisu(cards, eye)) // 检查字
		return false;

	if (!check_color_huisu(&cards[0], eye)) //检查万
		return false;

	if (!check_color_huisu(&cards[9], eye)) //检查条
		return false;

	if (!check_color_huisu(&cards[18], eye)) //检查筒
		return false;

	return true;
}

void hu_huisu_test(){
	unsigned char cards[] = {
		3, 1, 1, 1, 1, 2, 1, 1, 3,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0,
	};

	unsigned char cards1[] = {
		0, 0, 0, 2, 0, 0, 0, 0, 0,
		0, 0, 0, 3, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0,
	};

	unsigned char cards2[] = {
		1, 1, 1, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 1, 1, 1, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		3, 0, 0, 0, 0, 0, 2,
	};

	unsigned char cards3[] = {
		1, 1, 1, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 1, 4, 1, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 2,
	};

	unsigned char cards4[] = {
		1, 1, 1, 0, 0, 0, 0, 0, 0,
		0, 0, 1, 1, 4, 1, 1, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 3,
	};

	unsigned char cards5[] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		3, 2, 0, 0, 2, 0, 4,
	};

	unsigned char cards6[] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		3, 2, 0, 0, 2, 0, 1,
	};

	cout << "cards   ->  hu : " << check_hu_huisu(cards) << endl;
	cout << "cards1  ->  hu : " << check_hu_huisu(cards1) << endl;
	cout << "cards2  ->  hu : " << check_hu_huisu(cards2) << endl;
	cout << "cards3  ->  hu : " << check_hu_huisu(cards3) << endl;
	cout << "cards4  ->  hu : " << check_hu_huisu(cards4) << endl;
	cout << "cards5  ->  hu : " << check_hu_huisu(cards5) << endl;
	cout << "cards6  ->  hu : " << check_hu_huisu(cards6) << endl;
}
