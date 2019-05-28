#include <io.h>
#include <time.h>
#include <direct.h>
#include <windows.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

string FilePath = "./cards.dat";
string DirName = "./_CardsRecord";

//long 转成 string
inline string ltos(long l)
{
	ostringstream os;
	os << l;
	string result;
	istringstream is(os.str());
	is >> result;
	return result;
}

//10进制转成16进制
inline string Int2Dec(int num)
{
	string str;
	int temp = num / 16;
	int left = num % 16;

	if (temp > 0)
		str += Int2Dec(temp);

	if (left < 10)
		str += left + '0';
	else
		str += left + 'A' - 10;
	return str;
}

inline int FindIndex(unsigned char cards[], int count, unsigned char cardData)
{
	for (int i = 0; i < count; i++)
	{
		if (cards[i] == cardData)
			return i;
	}
	return -1;
}

inline void PRINT_CARDS(unsigned char allCards[], int allCount)
{
	int cc = 1;
	for (int i = 0; i < allCount; i++)
	{
		if (allCards[i] < 10)
			printf("0x0%-2x", allCards[i]);
		else
			printf("0x%-3x", allCards[i]);
		if (cc++ % 10 == 0)
			putchar(10);
	}
	putchar(10);
}

class CCardTool
{
public:
	CCardTool();
	~CCardTool();

	static void WriteCardsRecord(unsigned char cards[], int count, long = 0, long = 0);
	static void peipai_func(unsigned char allCards[], int allCount);

	static void WriteCardsToFile(unsigned char cards[], int count, string path);
	static int ReadCardsFromFile(unsigned char *buf);

private:
	unsigned char m_cards[136];
};

CCardTool::CCardTool()
{
	if (_access(DirName.c_str(), 0) == -1)
		_mkdir(DirName.c_str());
}

CCardTool::~CCardTool()
{
}

void CCardTool::WriteCardsRecord(unsigned char cards[], int count, long tableId, long payCount)
{

	long myt = time(NULL);

	string str = "";
	string tableStr = "table_" + ltos(tableId) + "_" + ltos(payCount) + "_" + ltos(myt);

	WriteCardsToFile(cards, count, DirName + "/" + tableStr + ".dat");
	ofstream out(DirName + "/" + tableStr + ".log", ios::app);

	SYSTEMTIME sys;
	GetLocalTime(&sys);
	out << "////日期：" << sys.wYear << ":" << sys.wMonth << ":" << sys.wDay
		<< " ,  时间:  " << sys.wHour << ":" << sys.wMinute << ":" << sys.wSecond
		<< " ,  时间戳:  " << myt << endl;
	out << "////桌子ID：" << tableId << ", 当前局数:  " << payCount << endl;

	int cctimer = 1;
	out << "unsigned char " + tableStr + "[] = { " << endl;
	for (int i = 0; i < count; i++)
	{
		if (cards[i] < 10)
			str = "0x0" + Int2Dec(cards[i]);
		else
			str = "0x" + Int2Dec(cards[i]);
		out << str << ", ";
		if (cctimer++ % 10 == 0)
			out << endl;
	}
	out << "}" << endl
		<< endl;

	out.close();
	return;
}

void CCardTool::WriteCardsToFile(unsigned char cards[], int count, string path)
{
	CCardTool s;
	ofstream outFile(path, ios::out | ios::binary); //二进制方式写
	outFile.write((char *)&(s), sizeof(s));
	cout << sizeof(s) << endl;
	outFile.close();
}

int CCardTool::ReadCardsFromFile(unsigned char *buf)
{
	ifstream inFile(FilePath, ios::in | ios::binary); //二进制方式读
	if (!inFile)
		return -1;

	int readLen = 0;
	char ch[1];
	while (!inFile.eof())
	{
		inFile.read(ch, 1);
		buf[readLen++] = ch[0];
	}
	inFile.close();

	return readLen;
}

void CCardTool::peipai_func(unsigned char allCards[], int allCount)
{
	unsigned char buff[512];
	unsigned char readCount = CCardTool::ReadCardsFromFile(buff);

	if (allCount < --readCount)
		return;
	memcpy(allCards, buff, readCount);
	return;

	//unsigned char buff[] = {
	//	0x11, 0x11, 0x11, 0x11, 0x12, 0x12, 0x12, 0x12, 0x13, 0x13, 0x13, 0x13, 0x14,  //玩家1
	//	0x15, 0x15, 0x15, 0x15, 0x16, 0x16, 0x16, 0x16, 0x17, 0x17, 0x17, 0x17, 0x14,  //玩家2
	//	0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x31, 0x31, 0x31, 0x14,  //玩家3
	//	0x26, 0x27, 0x28, 0x28,
	//};
	//int readCount = sizeof(buff) / sizeof(unsigned char);

	//for (int i = 0; i < readCount; i++){
	//	auto cardData = buff[i];
	//	auto index = FindIndex(allCards, allCount - i, cardData);
	//	auto index1 = allCount - 1 - i;
	//	if (index != -1)
	//		std::swap(allCards[index], allCards[index1]);
	//}
	//return;
}


int main_test()
{
	unsigned char cards[] = {
		0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
		0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
		0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
		0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
		0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19,
		0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19,
		0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19,
		0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19,
		0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,
		0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,
		0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,
		0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,
		0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
		0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
		0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
		0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, };

	int size = sizeof(cards) / sizeof(unsigned char);

	srand((unsigned)time(0));
	random_shuffle(cards, cards + size);

	CCardTool::peipai_func(cards, size);
	CCardTool::WriteCardsRecord(cards, size);

	PRINT_CARDS(cards, size);
	return 0;
}

