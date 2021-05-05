#include <stdio.h>
#include "main.h"

int ChangePlus(int n, char* str, int index)
{
	printf("(");
	while (n < str[index] - 48)
	{
		printf("+");
		n++;
	}
	printf(")");

	return n;
}

int ChangeMinus(int n, char* str, int index)
{
	printf("(");
	while (n < str[index] - 48)
	{
		printf("-");
		n++;
	}
	printf(")");

	return n;
}

int main()
{
	char text[1000];
	char plus[5] = { '1', '3', '5', '7', '9' };
	char minus[5] = { '2', '4', '6', '8', '0' };
	char ch;
	int I = 0;
	puts("Input:");
	while ((ch = getchar()) != '\n')
	{
		for (int i = 0; i < 5; i++)
		{
			if (ch == plus[i])
			{
				int a = 0;
				ChangePlus(a, plus, i);
			}
			if (ch == minus[i])
			{
				int a = 0;
				ChangeMinus(a, minus, i);
			}
		}
		if (ch < '0' || ch > '9')
			printf("%c", ch);
		I++;
	}
	text[I] = '\0';
	return 0;
}