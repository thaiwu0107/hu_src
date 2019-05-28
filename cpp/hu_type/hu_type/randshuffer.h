
#include <time.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<list>
#include<set>
#include<map>
using namespace std;

int getCardCount(vector<unsigned char> cards, unsigned char card){
	int count = 0;
	for (int i = 0; i < cards.size(); i++){
		if ((cards[i] & 0x0f) == (card & 0x0f))
			++count;
	}
	return count;
}

int randBombCountByRate(float rate)
{
	int bombCount = 0;
	if (rand() % 100 < rate * 100){
		//根据玩家的胜率rate进行概率随机炸弹
		//随机到1、2、3、4个炸弹的概率为40%，30%，20%，%10
		int rand2 = rand() % 100; 
		if (rand2 >= 0 && rand2 < 40)
			bombCount = 1;
		else if (rand2 < 70)
			bombCount = 2;
		else if (rand2 < 90)
			bombCount = 3;
		else 
			bombCount = 4;
	}
	return bombCount;
}

void randBomb(vector<unsigned char> allCards, vector<unsigned char> &bombCards, int bombCount)
{
	srand(((unsigned)time(0)));
	set<unsigned char>bombSet;
	
	int bombRandCount = 0;
	while (bombRandCount < bombCount){
		int bomoIdx = rand() % allCards.size();
		unsigned char bomoCard = allCards[bomoIdx];

		if (bomoCard == 0x4e || bomoCard == 0x4f){
			bombSet.insert(0x4e);
		}
		else{
			unsigned char bomoCardValue = bomoCard & 0x0f;
			bombSet.insert(bomoCardValue);
		}
		bombRandCount = bombSet.size();
	}
	for (auto elem : bombSet){
		if (elem == 0x4e)
		{
			bombCards.push_back(0x4e);
			bombCards.push_back(0x4f);
		}
		else{
			bombCards.push_back(elem | 0x00);
			bombCards.push_back(elem | 0x10);
			bombCards.push_back(elem | 0x20);
			bombCards.push_back(elem | 0x30);
		}
	}
	return ;
}

void initBottomCard(vector<unsigned char> allCards, vector<unsigned char> &bombCards, vector<unsigned char> &bottomCards){
	int RandCount = 0;
	while (RandCount < 3)
	{
		int idx = rand() % allCards.size();
		unsigned char card = allCards[idx];
		int count = getCardCount(bombCards, card);
		if (count == 0){
			bottomCards.push_back(card);
			++RandCount;
		}
	}
}

// allCards[0,54]  = playerCards + bombCards + bottomCards 
void initPlayersCard(vector<unsigned char> allCards, vector<unsigned char> &playerCards, vector<unsigned char> &bombCards, vector<unsigned char> &bottomCards)
{
	vector<unsigned char>mgr;
	for (auto i : bombCards)
		mgr.push_back(i);
	for (auto i : bottomCards)
		mgr.push_back(i);

	for (int i = 0; i < mgr.size(); i++){
		for (int j = 0; j < allCards.size(); j++){
			if (allCards[j] == mgr[i])
				std::swap(allCards[j], allCards[allCards.size() - 1 - i]);
		}
	}

	for (auto it = allCards.begin(); it != allCards.end() - mgr.size(); it++)
		playerCards.push_back(*it);

	random_shuffle(playerCards.begin(), playerCards.end()); //可以再打乱一次3个玩家的手牌
}

void splitPlayerBomb(vector<unsigned char> &playerCards)
{
	int maxBombCount[3];
	vector<unsigned char> tmp[3];
	int playerCardsCount = playerCards.size();

	int i = 0;
	while (i < playerCards.size())
	{
		auto j = i / 17;
		auto card = playerCards[i];
		auto cardValue = card & 0x0f;
		auto cardCount = getCardCount(tmp[j], card);
	
		if (tmp[j].size() == 0 || cardCount <= 3){
			tmp[j].push_back(card);
			i++;
		}
		else if ((cardCount == 4) && (cardValue >= 3 && cardValue <= 7) && (maxBombCount[j] == 0)){
			maxBombCount[j]++;
			tmp[j].push_back(card);
			i++;
		}
		else if (cardCount == 4){
			int idx = rand() % (playerCardsCount - i) + i;
			std::swap(playerCards[i], playerCards[idx]);
		}
	}

	playerCards.clear();
	for (auto j = 0; j < 3; j++){
		for (auto i : tmp[j])
			playerCards.push_back(i);
	}
	return;

}

//重组所有牌 ,[0-3]:bottom,[3-37]:其余两玩家的手牌, [37-54]:方位为chairid的手牌
void reBuildCards(unsigned char result[54], vector<unsigned char> &playerCards, vector<unsigned char> &bombCards, vector<unsigned char> &bottomCards, int chairid)
{
	vector<unsigned char>mgr;
	for (auto i : playerCards)
		mgr.push_back(i);
	for (auto i : bombCards)
		mgr.push_back(i);

	vector<unsigned char>tmp[3];
	for (int i = 0; i < mgr.size(); i++){
		int j = i / 17;
		tmp[j].push_back(mgr[i]);
	}

	for (int i = 0; i < 17; i++){
		std::swap(tmp[2].at(i), tmp[2-chairid].at(i));
	}

	int count = 0;
	for (auto i : bottomCards)
		result[count++] = i;
	for (auto i : tmp[0])
		result[count++] = i;
	for (auto i : tmp[1])
		result[count++] = i;
	for (auto i : tmp[2])
		result[count++] = i;
	return;
}

void main_shuffleRate(unsigned char result[54], unsigned char oneCards[], int oneCardsCount, float rate, int chairid)
{
	vector<unsigned char>allCards, bombCards, bottomCards, playerCards;
	for (int i = 0; i < oneCardsCount; ++i) allCards.push_back(oneCards[i]);

	int bombCount = randBombCountByRate(rate);			  //根据概率随机炸弹
	randBomb(allCards, bombCards, bombCount);			  //获取炸弹牌堆
	initBottomCard(allCards, bombCards, bottomCards);	  //获取底牌牌堆
	initPlayersCard(allCards, playerCards, bombCards, bottomCards); //获取玩家牌堆

	splitPlayerBomb(playerCards);                       //拆炸弹
	reBuildCards(result, playerCards, bombCards, bottomCards, chairid); //重组牌堆

	//printf("\n炸弹,个数:%d, 数据: ",bombCount);
	//for (auto i : bombCards)
	//	printf("0x%-2x ", i);
	//printf("\nbottom：");
	//for (auto i : bottomCards)
	//	printf("0x%-2x ", i);

	return;
}

bool check(unsigned char result[54], unsigned char oneCards[54])
{
	sort(result, result + 54);
	sort(oneCards, oneCards + 54);

	for (int i = 0; i < 54; i++){
		if (result[i] != oneCards[i])
		{
			printf("bad test----\n");
			return false;
		}
	}
	return true;
}

int main_shuffleRate_test(){

	int testCount = 1;
	float rate = (rand() % 10000) * 100;
	while (testCount <= 100)
	{
		srand(((unsigned)time(0))+testCount);
		printf("**********************开始测试第%d组数据：", testCount);
		
		unsigned char oneCards[] = {
			0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x01, 0x02, 		//黑桃
			0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x11, 0x12,		//红桃
			0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x21, 0x22,		//梅花
			0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x31, 0x32,		//方块
			0x4e, 0x4f,																			//大小王
		};
		int oneCardsCount = sizeof(oneCards) / sizeof(unsigned char);

		random_shuffle(oneCards, oneCards+oneCardsCount);
		for (int i = 0; i < oneCardsCount; i++){
			int idx = rand() % (oneCardsCount - i) + i;
			std::swap(oneCards[i], oneCards[idx]);
		}

		unsigned char result[54];
		main_shuffleRate(result, oneCards, oneCardsCount, 0.5, 0);

		
		bool beOk = true;
		unsigned char tmp1[54], tmp2[54];
		memcpy(tmp1, result, 54);
		memcpy(tmp2, oneCards,54);
		for (int i = 0; i < 54; i++){
			if (tmp1[i] != tmp2[i])
			{
				beOk = false;
				break;
			}
		}

		if (beOk == false)
			continue;
		
		printf("\nresult：\n");
		printf("底牌为：0x%x,0x%x,0x%x\n", result[0], result[1], result[2]);
		for (int j = 0; j < 3; j++){
			printf("手牌%d ：", j);
			for (int i = 0; i < 17; i++){
				printf("0x%-2x ", result[j * 17 + 3 + i]);
			}
			putchar(10);
		}
		//cout << "-----》cout = " << count << endl;
		//printf("第%d组数据测试完毕！$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n\n", testCount++);
		_sleep(500);

	}
	
	return 0;
}
