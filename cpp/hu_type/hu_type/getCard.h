
#include<iostream>
using namespace std;
//
//unsigned char my_cards[] = {
//	0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,						//万子
//	0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,						//万子
//	0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,						//万子
//	0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,						//万子
//	0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19,						//索子
//	0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19,						//索子
//	0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19,						//索子
//	0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19,						//索子
//	0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,						//同子
//	0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,						//同子
//	0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,						//同子
//	0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,						//同子
//	0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,									//东西南北中发白
//	0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,									//东西南北中发白
//	0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,									//东西南北中发白
//	0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,									//东西南北中发白
//};
//
//void setLaiZi____________(){
//	cout << "玩法中设置癞子成功！" << endl;
//}
//
////playerNum : 玩家人数   , notWind:不带风 ,   laiZi:红中混牌,    queMen:缺门
//void printSetCfg(int playerNum, bool notWind, bool laiZi, bool queMen){
//	cout << "玩家人数:" << playerNum << " ,不带风：" << notWind << " ,红中混牌：" << laiZi << " , " << "缺门：" << queMen << endl;
//}
//
//void printCards_111(unsigned char cards[], int n){
//	for (int i = 0; i<n; i++){
//		printf("0x%-2x ", cards[i]);
//		if ((i + 1) % 9 == 0)
//			putchar(10);
//	}
//	putchar(10);
//}
//
////playerNum : 玩家人数   , notWind:不带风 ,   laiZi:红中混牌,    queMen:缺门
//int getPokerCards(unsigned char tmpCards[136], int playerNum, bool notWind, bool laiZi, bool queMen){
//
//	memset(tmpCards, 0, 136);
//	printSetCfg(playerNum, notWind, laiZi, queMen);
//
//	int cardsCount = 0;
//
//	//玩家人数：4 ， 带风 
//	if ((playerNum == 4) && (notWind == false))
//	{
//		cardsCount = 136;
//		memcpy(tmpCards, my_cards, 136);
//		if (laiZi)  //红中混牌
//			setLaiZi____________();
//		return cardsCount;
//	}
//
//	//玩家人数：4 ， 不带风 
//	if ((playerNum == 4) && (notWind == true))
//	{
//		cardsCount = 108;
//		memcpy(tmpCards, my_cards, 108);
//
//		if (laiZi == true)//红中混牌 , 112 = 108 +4
//		{
//			for (int i = 0; i<4; i++)
//				tmpCards[108 + i] = 0x35;
//			setLaiZi____________();
//			cardsCount += 4;
//		}
//		return cardsCount;
//	}
//
//
//	//玩家人数：3 ， 带风 
//	if ((playerNum == 3) && (notWind == false))
//	{
//		//缺门
//		if (queMen == true)
//		{
//			cardsCount = 100;
//			memcpy(tmpCards, my_cards + 36, cardsCount);
//			if (laiZi == true)
//				setLaiZi____________();
//			return cardsCount;
//		}
//
//		//非缺门
//		else if (queMen == false)
//		{
//			cardsCount = 136;
//			memcpy(tmpCards, my_cards, cardsCount);
//			if (laiZi)
//				setLaiZi____________();
//			return cardsCount;
//		}
//	}
//
//	//玩家人数：3 ， 不带风 
//	if ((playerNum == 3) && (notWind == true))
//	{
//		//缺门
//		if (queMen == true)
//		{
//			cardsCount = 72;
//			memcpy(tmpCards, my_cards + 36, 72);
//
//			if (laiZi == true)
//			{
//				for (int i = 0; i<4; i++)
//					tmpCards[72 + i] = 0x35;
//				setLaiZi____________();
//				cardsCount += 4;
//			}
//			return cardsCount;
//		}
//
//		//非缺门
//		else if (queMen == false)
//		{
//			cardsCount = 108;
//			memcpy(tmpCards, my_cards, 108);
//
//			if (laiZi == true)
//			{
//				for (int i = 0; i<4; i++)
//					tmpCards[108 + i] = 0x35;
//				setLaiZi____________();
//				cardsCount += 4;
//			}
//			return cardsCount;
//		}
//	}
//}
//
//
//void getPokerCards_test(){
//	int playerNum = 4;//玩家人数
//	bool notWind = 1;//不带风
//	bool laiZi = 1;//红中混牌
//	bool queMen = 0;//缺门
//
//	unsigned char tmpCards[136];
//	memcpy(tmpCards, my_cards, 136);
//	int num = getPokerCards(tmpCards, playerNum, notWind, laiZi, queMen);
//	printCards_111(tmpCards, num);
//	cout << "当前玩法中，扑克总数为：" << num << endl;
//
//
//}