#pragma once

#include <cstring>
#include "string.h"

#include "data.h"

class hu_type
{

public:
	static bool check_hu(const unsigned char temp_cards[], unsigned char temp_gui_index);     //hu
	static bool check_hu_258(const unsigned char temp_cards[], unsigned char temp_gui_index); //hu 258
private:
	static bool get_cache(char *cards, char max_gui, int *cache);
	static bool check_color(char *cards, char from, char gui_num);
	static bool check_color_258(char *cards, char from, char gui_num);
	static int check_normal(char *cards, int from, int max_gui, int used_gui);
	static int next_split(char *cards, int gui_num, int max_gui, int used_gui);
	static void one(char *cards, int &index, int &need_gui, int max_gui, int used_gui);
	static void two(char *cards, int &index, int &need_gui, int max_gui, int used_gui);
	static inline int check_zi(char *cards);

public:
	static int m_haohuaNum;

public:
	static bool Is_13_19(const unsigned char cbCardIndex[], unsigned char gui_index = 34);
	static bool IsQiXiaoDui(const unsigned char cards[], unsigned char gui_index = 34);

	static bool IsPengPeng(const unsigned char cbCardIndex[], const tagWeaveItem WeaveItem[], unsigned char cbItemCount, unsigned char gui_index = 34);
	static bool IsQingYiSe(const unsigned char cbCardIndex[], const tagWeaveItem WeaveItem[], const unsigned char cbItemCount, unsigned char gui_index = 34);
	static bool IsHunYiSe(const unsigned char cbCardIndex[], const tagWeaveItem WeaveItem[], const unsigned char cbItemCount, unsigned char gui_index = 34);
	static bool IsZiYiSe(const unsigned char cbCardIndex[], const tagWeaveItem WeaveItem[], const unsigned char cbItemCount, unsigned char gui_index = 34);
	static bool IsYiTiaoLong(const unsigned char cbCardIndex[], unsigned char gui_index = 34);
	static bool IsKaZhang(const unsigned char cbCardIndex[], unsigned char targetCard, unsigned char gui_index = 34);
	static bool IsShunZiHu(const unsigned char cbCardIndex[], unsigned char gui_index = 34);
	static bool check_foreach_eye(char *cards, char gui_num);
	static int check_foreach_color_need(char *cards, int from, int to);
	static bool IsHuaLong(const unsigned char cards[], unsigned char gui_index = 34);
	static int removeAndGetNeed(unsigned char tmpCards[], int Colors[3]);
};
