#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "Source.h"
#include "List.h"
#include "Checker.h"
#include <time.h>

int difference(char* pattern)
{
	char* temp = (char*)calloc(5, sizeof(char));
	for (int i = 6, j = 0; i < 10; i++, j++)
	{
		temp[j] = pattern[i];
	}
	struct tm* mTime;
	time_t t = time(NULL);
	mTime = localtime(&t);
	int year = atoi(temp);
	free(temp);
	if (year < mTime->tm_year + 1900)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

char* lltoa(long long val, int base)
{
	static char buf[64] = { 0 };
	int i = 62;
	int sign = (val < 0);
	if (sign)
	{
		val = -val;
	}
	if (val == 0)
	{
		return 0;
	}
	for (; val && i; --i, val /= base)
	{
		buf[i] = "0123456789abcdef"[val % base];
	}
	if (sign)
	{
		buf[i--] = '-';
	}
	return &buf[i + 1];
}

char* toString(unsigned long long int account)
{
	unsigned long long int temp = 0;
	temp = account;
	int count = 0;
	while (temp)
	{
		temp /= 10;
		count++;
	}
	char* result = (char*)calloc(count + 5, sizeof(char));
	if (result == NULL)
	{
		return NULL;
	}
	strcpy(result, lltoa(account, 10));
	strcpy((result + count), ".txt");
	return result;
}

void delete_string(unsigned long long int account)
{
	char* txt = toString(account);
	FILE* f = fopen(txt, "r");
	if (f != NULL)
	{
		int const size = 1024;
		char pattern[size];
		fseek(f, 0, SEEK_END);
		char* storyData = (char*)calloc(ftell(f) + 1, sizeof(char));
		char* ptr = storyData;
		*ptr = 0;
		fseek(f, 0, SEEK_SET);
		while (fgets(pattern, size, f))
		{
			if (difference(pattern) == 0)
			{
				strcat(ptr, pattern);
				ptr += strlen(pattern);
			}
		}
		fclose(f);
		f = fopen(txt, "w");
		fputs(storyData, f);
		fclose(f);
		free(txt);
		free(storyData);
	}
}

void loadToFile(unsigned long long int account, const char* what, int sum)
{
	delete_string(account);
	FILE* fp;
	struct tm* mTime;
	time_t t = time(NULL);
	mTime = localtime(&t);
	char* txt = toString(account);
	fp = fopen(txt, "a");
	if (fp == NULL)
	{
		printf("Can't open file");
		return;
	}
	fprintf(fp, "%02d.%02d.%02d account id: %lld. What happend: %s %d \n", mTime->tm_mday, mTime->tm_mon + 1, 1900 + mTime->tm_year, account, what, sum);
	fclose(fp);
	free(txt);
}

void GetBalance(struct List* list, unsigned long long int accountNumber)
{
	struct Node* temp = FindAccount(list->head, accountNumber);
	if (temp == NULL)
	{
		printf("Invalid account");
		return;
	}
	else
	{
		ShowDeposit(temp);
		int indexDeposit = check("Please enter index: ", 0, temp->depSize + 2);
		indexDeposit--;
		struct Deposit* dep = findDeposit(temp, indexDeposit);
		if (dep == NULL)
		{
			printf("Invalid deposit\n");
			return;
		}
		printf("Balance: %d\n", dep->balance);
		loadToFile(accountNumber, "Check Balance: ", dep->balance);
	}
}

void PutMoney(struct List* list, unsigned long long int accountNumber, int sum)
{
	struct Node* temp = FindAccount(list->head, accountNumber);
	if (temp == NULL)
	{
		printf("Invalid account\n");
		return;
	}
	else
	{
		ShowDeposit(temp);
		int indexDeposit = check("Please enter number: ", 0, temp->depSize + 2);
		indexDeposit--;
		struct Deposit* dep = findDeposit(temp, indexDeposit);
		if (dep == NULL || dep->isLock == 0)
		{
			printf("Invalid deposit or cant add deposit\n");
			return;
		}
		dep->balance += sum;
		printf("Money was added. Balance: %d\n", dep->balance);
	}
	loadToFile(accountNumber, "Money was added to account: +", sum);
}

void GetMoney(struct List* list, unsigned long long int accountNumber, int sum)
{
	struct Node* temp = FindAccount(list->head, accountNumber);
	if (temp == NULL)
	{
		printf("Invalid passport series\n");
		return;
	}
	else
	{
		ShowDeposit(temp);
		int indexDeposit = check("Please enter number: ", 0, temp->depSize + 2);
		indexDeposit--;
		struct Deposit* dep = findDeposit(temp, indexDeposit);
		if (dep == NULL || dep->isLock == 1 || dep->balance < sum)
		{
			printf("Invalid deposit or can't get deposit");
			return;
		}
		dep->balance -= sum;
		printf("Money debited from your account. Balance: %d\n", dep->balance);
		loadToFile(accountNumber, "Money debited account: -", sum);
	}
}

double GetPercent(int sum, const char* from, const char* to)
{
	int day[2] = { (int)(from[0]) * 10 + (int)(from[1]), (int)(to[0]) * 10 + (int)(to[1]) };
	int month[2] = { (int)(from[3]) * 10 + (int)(from[4]), (int)(to[3]) * 10 + (int)(to[4]) };
	int year[2] = { (int)(from[6]) * 1000 + (int)(from[7]) * 100 + (int)(from[8]) * 10 + (int)(from[9]), (int)(to[6]) * 1000 + (int)(to[7]) * 100 + (int)(to[8]) * 10 + (int)(to[9]) };
	int resYear = year[1] - year[0];
	int resMonth = month[1] - month[0];
	int resDay = day[1] - day[0];
	if (resDay < 0)
	{
		resDay += 30;
		resMonth--;
	}
	if (resMonth < 0)
	{
		resMonth += 12;
		resYear--;
	}
	if (resYear < 0)
	{
		printf("Incorrect date\n");
		return 0;
	}
	int time = resDay + resMonth * 30 + resYear * 365;
	return (sum * 11.5 * time) / (365 * 100);
}

void transfer(struct List* list, unsigned long long int from, unsigned long long int to, int sum)
{
	struct Deposit* dep1;
	struct Node* temp = FindAccount(list->head, from);
	if (temp == NULL)
	{
		printf("Invalid account\n");
		return;
	}
	else
	{
		ShowDeposit(temp);
		int indexDeposit = check("Please enter number: ", 0, temp->depSize + 2);
		indexDeposit--;
		dep1 = findDeposit(temp, indexDeposit);
	}
	struct Deposit* dep2;
	temp = FindAccount(list->head, to);
	if (temp == NULL)
	{
		printf("Invalid account\n");
		return;
	}
	else
	{
		ShowDeposit(temp);
		int indexDeposit = check("Please enter number: ", 0, temp->depSize + 2);
		indexDeposit--;
		dep2 = findDeposit(temp, indexDeposit);
	}
	if (dep1 != NULL && dep1->isLock != 0 && dep2 != NULL && dep2->isLock != 1 && sum < dep1->balance)
	{
		dep1->balance -= sum;
		dep2->balance += sum;
		loadToFile(from, "Money debited account: -", sum);
		loadToFile(to, "Money was added to account: +", sum);
		printf("Succesfull\n");
	}
	else
	{
		printf("Error to tranfer money.\n");
	}
}

void ShowHistory(unsigned long long int account)
{
	char* txt = toString(account);
	FILE* f = fopen(txt, "r");
	if (f != NULL)
	{
		int const size = 1024;
		char pattern[size];
		fseek(f, 0, SEEK_SET);
		while (fgets(pattern, size, f))
		{
			printf("%s", pattern);
		}
		fclose(f);
	}
	free(txt);
}

unsigned long long int hashing_(char* key)
{
	int count = strlen(key);
	count += 17;
	char* temp = (char*)calloc(count + 16, sizeof(char));
	temp = strcpy(temp, key);
	strcpy((temp + count - 17), "3Ogh45TH24oEQWE");
	int lengthHash = 10;
	int modHash = 100000000;
	const int HEX = 16;
	unsigned long long int hash = 0, p = temp[0];
	for (int i = 0; i < count; i++)
	{
		p *= (p + (int)temp[i]);
		hash += ((int)temp[i] * p);
		if (hash > modHash * modHash)
		{
			hash = hash / modHash + hash % modHash;
			p = temp[0];
		}
	}
	int i = 0;
	int hashCount = count;
	while (hashCount < lengthHash)
	{
		hash += (((int)temp[i] * i + (int)temp[i - 1] % HEX + hashCount * hash) % 10) * count;
		i++;
		if (i > count)
		{
			i = 0;
		}
		hashCount++;
	}
	return hash;
}

unsigned long long int hashing(char* key)
{
	return hashing_(key);
}