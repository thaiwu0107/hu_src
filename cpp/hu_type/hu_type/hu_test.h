#include"hu_type.h"

#include<iostream>
using namespace std;

void hu_test(){
	unsigned char cards[] = {
		3, 1, 1, 1, 1, 1, 1, 1, 3,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 1,
	};

	unsigned char cards1[] = {
		0, 0, 0, 1, 0, 0, 0, 0, 0,
		0, 0, 0, 3, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 1,
	};

	unsigned char cards2[] = {
		1, 1, 1, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 1, 1, 1, 0, 0, 0,
		0, 0, 2, 0, 0, 0, 0, 0, 0,
		2, 0, 0, 0, 0, 0, 2,
	};

	unsigned char cards3[] = {
		1, 1, 1, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 1, 2, 1, 0, 0, 0,
		0, 0, 2, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 2,
	};

	unsigned char cards4[] = {
		1, 0, 1, 0, 0, 0, 1, 1, 0,
		0, 0, 2, 0, 0, 0, 0, 3, 0,
		0, 0, 0, 1, 1, 3, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0,
	};

	unsigned char gui_index = 23;
	//cout << "cards   ->  hu : " << hu_type::check_hu(cards, gui_index) << endl;
	//cout << "cards1  ->  hu : " << hu_type::check_hu(cards1, gui_index) << endl;
	//cout << "cards2  ->  hu : " << hu_type::check_hu(cards2, gui_index) << endl;
	//cout << "cards3  ->  hu : " << hu_type::check_hu(cards3, gui_index) << endl;
	cout << "cards4  ->  hu : " << hu_type::check_hu(cards4, gui_index) << endl;
}

void hu_258_test(){


	unsigned char cards[] = {
		1, 1, 1, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 1, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		2, 0, 0, 0, 0, 0, 1,
	};

	unsigned char cards1[] = {
		1, 1, 1, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 1, 1, 1, 0, 0, 0,
		0, 1, 0, 0, 0, 0, 0, 0, 0,
		2, 0, 0, 0, 0, 0, 2,
	};

	unsigned char cards2[] = {
		1, 1, 1, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 1, 1, 1, 0, 0, 0,
		0, 0, 2, 0, 0, 0, 0, 0, 0,
		2, 0, 0, 0, 0, 0, 2,
	};

	unsigned char cards3[] = {
		1, 1, 1, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 1, 2, 1, 0, 0, 0,
		0, 0, 2, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 2,
	};

	unsigned char cards4[] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		3, 2, 0, 0, 2, 0, 4,
	};

	unsigned char cards5[] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		3, 2, 0, 0, 2, 0, 1,
	};

	unsigned char gui_index = 33;
	cout << "cards  -> hu_258 : " << hu_type::check_hu_258(cards, gui_index) << endl;
	cout << "cards1 -> hu_258 : " << hu_type::check_hu_258(cards1, gui_index) << endl;
	cout << "cards2 -> hu_258 : " << hu_type::check_hu_258(cards2, gui_index) << endl;
	cout << "cards3 -> hu_258 : " << hu_type::check_hu_258(cards3, gui_index) << endl;
	cout << "cards4 -> hu_258 : " << hu_type::check_hu_258(cards4, gui_index) << endl;
	cout << "cards5 -> hu_258 : " << hu_type::check_hu_258(cards5, gui_index) << endl;
}

void IsPengPengHu_test(){
	unsigned char cards[] = {
		3, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 2, 0, 0, 0, 0, 2,
	};


	unsigned char cards1[] = {
		1, 1, 2, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 4,
	};

	unsigned char cards2[] = {
		0, 3, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 2, 3,
	};

	tagWeaveItem WeaveItem[4];

	cout << "card  -> pengPeng_hu        : " << hu_type::IsPengPeng(cards, WeaveItem, 0, 33) << endl;
	cout << "card  -> pengPeng_hu (Ó²ºú) : " << hu_type::IsPengPeng(cards, WeaveItem, 0, 34) << endl;

	cout << "card1 -> pengPeng_hu        : " << hu_type::IsPengPeng(cards1, WeaveItem, 0, 33) << endl;
	cout << "card1 -> pengPeng_hu (Ó²ºú) : " << hu_type::IsPengPeng(cards1, WeaveItem, 0, 34) << endl;

	cout << "card2 -> pengPeng_hu        : " << hu_type::IsPengPeng(cards2, WeaveItem, 0, 33) << endl;
	cout << "card2 -> pengPeng_hu (Ó²ºú) : " << hu_type::IsPengPeng(cards2, WeaveItem, 0, 34) << endl;
}


void IsShunZiHu_test(){
	unsigned char cards[] = {
		1, 1, 1, 0, 0, 0, 0, 0, 0,
		0, 1, 0, 1, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 0, 0, 0, 0, 0, 2,
	};
	unsigned char gui_index = 33;
	cout << "IsShunZiHu:    " << hu_type::IsShunZiHu(cards, gui_index) << endl;

}

void IsHuaLong_test(){
	unsigned char cards0[] = {
		3, 1, 1, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 1, 1, 1, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 1, 1, 4,
		0, 0, 0, 0, 0, 0, 0,
	};

	unsigned char cards1[] = {
		3, 1, 1, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 1, 1, 1, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 0,
	};

	unsigned char cards2[] = {
		0, 1, 1, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 1, 1, 1,
		2, 0, 0, 0, 0, 0, 4,
	};

	unsigned char cards3[] = {
		1, 1, 1, 1, 1, 1, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 1, 1, 1,
		1, 1, 1, 0, 0, 0, 0, 0, 0,
		2, 0, 0, 0, 0, 0, 0,
	};

	unsigned char cards4[] = {
		3, 1, 1, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 1, 0, 1, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0,
	};


	unsigned char gui_index = 33;
	unsigned char gui_index1 = 0;
	unsigned char gui_index2 = 34;

	cout << "cards0 ->  IsHuaLong : " << hu_type::IsHuaLong(cards0, gui_index) << endl;
	cout << "cards1 ->  IsHuaLong : " << hu_type::IsHuaLong(cards1, gui_index) << endl;
	cout << "cards2 ->  IsHuaLong : " << hu_type::IsHuaLong(cards2, gui_index) << endl;
	cout << "cards3 ->  IsHuaLong : " << hu_type::IsHuaLong(cards3, gui_index) << endl;
	cout << "cards4 ->  IsHuaLong : " << hu_type::IsHuaLong(cards4, gui_index1) << endl;
	cout << "cards4 ->  IsHuaLong : " << hu_type::IsHuaLong(cards4, gui_index2) << endl;

}
