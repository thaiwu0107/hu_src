
#include<iostream>
using namespace std;

void mybyte_test()
{
	unsigned char a = -1;
	unsigned char b = 260;

	printf("%d,%d\n", a, b);
	printf("%d,%d,%d,%d,%d\n", sizeof(unsigned char), sizeof(unsigned short), sizeof(int), sizeof(long), sizeof(long long));
}