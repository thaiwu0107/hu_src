#include <stdio.h>
#include <time.h>

void print_cards(char* cards){
	auto sum = 0;
	for (int i = 0; i < 27; i++){
		printf("%d ", cards[i]);
		sum++;
		if (sum % 9 == 0)
			printf("\n");
	}

	printf("\n\n");
}

void split(char* cards, int k)
{
	for (int i = 0; i<9; ++i)
	{
		int bit = 3 * i;
		int n = (k&(7 << bit)) >> bit;
		cards[i] = n;
	}
	print_cards(cards);
}



char analyse(char* handcards, char*outcards){
	int card = 0;

	for (int i = 0; i <= 14; i=i*3+2)
	{
		split(handcards, 0);
	}

	return card;
}

void test_analyse()
{
    char handcards[] = {
      0,0,0,0,1,1,4,0,0,
      0,1,1,0,0,0,2,0,0,
      1,1,2,0,0,0,0,0,0
    };

    char outcards[] = {
      0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0,
      0,0,0,0,0,0,0,0,0
    };

	int begin = time(NULL);
    char card = analyse(handcards, outcards);
	int end = time(NULL);
    printf("card=%d, use %d seconds\n",card, end-begin);
	getchar();
}

int main_ai()
{
	test_analyse();
	return 0;
}

