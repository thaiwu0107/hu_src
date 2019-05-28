
#include<iostream>
using namespace std;

#define CHR_NULL				0x0000								//非胡类型
#define CHR_CHI_HU				0x0001								//平胡
#define CHR_CHI_HU_MAGIC		0x0002								//软平胡
#define CHR_SEVEN_PAIRS			0x0004								//七小对
#define CHR_SEVEN_PAIRS_MAGIC	0x0008								//软七小对
#define CHR_SUPER_SEVEN_PAIRS		0x0010								//豪华七小对
#define CHR_SUPER_SEVEN_PAIRS_MAGIC	0x0020								//豪华软七小对

int CheckSevevPairsHu2(unsigned char cbCardIndex[34], unsigned char cbMagicIndex)
{
	unsigned char cbMagicNum = 0;
	if (cbMagicIndex >= 0 && cbMagicIndex < 34)
		cbMagicNum = cbCardIndex[cbMagicIndex];

	unsigned char need = 0;
	unsigned char tmp[4] = { 0 };           //单张 对子 三张 四张的个数
	for (unsigned char i = 0; i < 34; i++) {
		auto c = cbCardIndex[i];
		if (c == 0 || i == cbMagicIndex) continue;
		if (c % 2 == 1) need++;
		tmp[c - 1]++;
	}

	bool hu = (need <= cbMagicNum) && ((cbMagicNum - need) % 2 == 0);

	if (need == 0 && hu){
		if (tmp[3] > 0 || cbMagicNum == 4)
			return CHR_SUPER_SEVEN_PAIRS;
		return CHR_SEVEN_PAIRS;
	}
	else if (need != 0 && hu){
		if (tmp[3] > 0)
			return CHR_SUPER_SEVEN_PAIRS_MAGIC;
		return CHR_SEVEN_PAIRS_MAGIC;
	}

	return CHR_NULL;
}


void my7duiTest(){
	unsigned char gui_index = 0;
	unsigned char cards4[] = {
		1, 2, 2, 2, 2, 2, 2, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 3, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0,
	};

	cout << "==> : " << CheckSevevPairsHu2(cards4, gui_index) << endl;
}