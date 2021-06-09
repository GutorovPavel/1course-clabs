#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "Checker.h"
#include "List.h"
#include "Source.h"

int engChecker(char* str, const char* eng)
{
	int len = strlen(str);
	for (int i = 0; i < len; i++)
	{
		if (strchr(eng, str[i]) == NULL)
		{
			return 1;
		}
	}
	return 0;
}

int check(const char* funcpointer, int min, int max)
{
	int num;
	char temp = '\n';
	do
	{
		printf("%s\n", funcpointer);
		if (scanf("%d%c", &num, &temp) == 2 && temp == '\n' && num > min && num < max)
		{
			break;
		}
		printf("Wrong input, press any key to continue\n");
		rewind(stdin);
		getchar();

	} while (1);
	return num;
}

char* DepositChecker(void)
{
	printf("1) Savings contribution\n");
	printf("2) Cumulative contribution\n");
	printf("3) Specialized contribution\n");
	int index = check("Enter number: ", 0, 4);
	char* temp = NULL;
	switch (index)
	{
	case 1:
		temp = (char*)calloc(21, sizeof(char));
		strcpy(temp, "Savings contribution");
		return temp;
	case 2:
		temp = (char*)calloc(24, sizeof(char));
		strcpy(temp, "Cumulative contribution");
		return temp;
	case 3:
		temp = (char*)calloc(25, sizeof(char));
		strcpy(temp, "Specialized contribution");
		return temp;
	}
	return temp;
}

char* StringChecker(const char* funcpointer, const char* eng)
{
	char* str = (char*)calloc(265, sizeof(char));
	do
	{
		printf("%s\n", funcpointer);
		scanf("%s", str);
		rewind(stdin);
		if (!engChecker(str, eng))
		{
			break;
		}
		printf("Wrong input\n");
	} while (1);
	return str;
}

unsigned long long int LongChecker(const char* funcpointer)
{
	unsigned long long int num;
	char temp = '\n';
	do
	{
		printf("%s\n", funcpointer);
		if (scanf("%lld%c", &num, &temp) == 2 && temp == '\n')
		{
			break;
		}
		printf("Wrong input, press any key to continue\n");
		rewind(stdin);
		getchar();
		system("cls");
	} while (1);
	return num;
}

int timeChecker(char* str)
{
	char timeAll[] = "1234567890";
	int len = strlen(str);
	if (len != 10)
	{
		return 1;
	}
	if (strchr("0123", str[0]) == NULL)
	{
		return 1;
	}
	if (str[0] == '3' && strchr("01", str[1]) == NULL)
	{
		return 1;
	}
	if (strchr(timeAll, str[1]) == NULL)
	{
		return 1;
	}
	if (str[2] != '.')
	{
		return 1;
	}
	if (strchr("01", str[3]) == NULL)
	{
		return 1;
	}
	if (str[3] == '1' && strchr("012", str[4]) == NULL)
	{
		return 1;
	}
	if (strchr(timeAll, str[4]) == NULL)
	{
		return 1;
	}
	if (str[5] != '.')
	{
		return 1;
	}
	for (int i = 6; i < 10; i++)
	{
		if (strchr(timeAll, str[i]) == NULL)
		{
			return 1;
		}
	}
	return 0;
}

char* GetTime(const char* str)
{
	char* time = (char*)calloc(11, sizeof(char));
	do
	{
		time = StringChecker(str, "1234567890,.");
		if (timeChecker(time) == 0)
		{
			break;
		}
		printf("Wrong input, please, try again\n");
	} while (1);
	return time;
}