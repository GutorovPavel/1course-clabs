#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "List.h"
#include "Source.h"
#include "Checker.h"

void AddAccount(struct List* list);

int main(void)
{
	struct List* list = (struct List*)calloc(1, sizeof(struct List));
	int switchMenu;
	unsigned long long int accountNumber;
	char* passportSeries;
	int sum;
	char* surname;
	struct Node* account;
	while (1)
	{
		switchMenu = 0;
		printf("//////////////////////////////////////////////\nMenu\n");
		printf("1) Add account\n");
		printf("2) Add deposit\n");
		printf("3) Search\n");
		printf("4) Sort deposit\n");
		printf("5) Balance\n");
		printf("6) Put money\n");
		printf("7) Get money\n");
		printf("8) Transfer money\n");
		printf("9) Account statement\n");
		printf("10) Calculate interest rate\n");
		printf("11) Remove account\n");
		printf("12) Remove deposit\n");
		printf("13) Print all accounts\n");
		printf("14) Exit\n");
		switchMenu = check("", -1, 15);
		switch (switchMenu)
		{
		case 1:
		{
			system("cls");
			AddAccount(list);
			break;
		}
		case 2:
		{
			system("cls");
			accountNumber = LongChecker("Please, enter account: ");
			struct Node* account = FindAccount(list->head, accountNumber);
			if (account != NULL)
			{
				char* depositCategory = DepositChecker();
				int Balance = check("Please, enter deposit summ: ", -1, 10000);
				AddDeposit(account, account->passortSeries, depositCategory, Balance);
			}
			else
			{
				printf("Invalid account\n");
			}
			break;
		}
		case 3:
		{
			system("cls");
			surname = StringChecker("Please, enter surname in latin: ", "qwertyuioplkjhgfdsazxcvbnmQWERTYUIOPLKJHGFDSAZXCVBNM");
			FindSurname(list->head, surname);
			free(surname);
			break;
		}
		case 4:
		{
			system("cls");
			accountNumber = LongChecker("Please, enter account: ");
			account = FindAccount(list->head, accountNumber);
			sort(account);
			break;
		}
		case 5:
		{
			system("cls");
			accountNumber = LongChecker("Please, enter account: ");
			GetBalance(list, accountNumber);
			break;
		}
		case 6:
		{
			system("cls");
			accountNumber = LongChecker("Please, enter account: ");
			sum = check("Please, enter deposit summ: ", -1, 10000);
			PutMoney(list, accountNumber, sum);
			break;
		}
		case 7:
		{
			system("cls");
			accountNumber = LongChecker("Please, enter account: ");
			sum = check("Please, enter deposit summ: ", -1, 10000);
			GetMoney(list, accountNumber, sum);
			break;
		}
		case 8:
		{
			system("cls");
			accountNumber = LongChecker("Please, enter account from we take: ");
			unsigned long long int to = LongChecker("Please, enter account to we add: ");
			sum = check("Please, enter deposit summ: ", -1, 10000);
			transfer(list, accountNumber, to, sum);
			break;
		}
		case 9:
		{
			system("cls");
			accountNumber = LongChecker("Please, enter account: ");
			ShowHistory(accountNumber);
			break;
		}
		case 10:
		{
			system("cls");
			sum = check("Please, enter deposit summ: ", -1, 10000);
			char* from_date = GetTime("Please, enter deposit openning date(##.##.####): ");
			char* to_date = GetTime("Please, enter deposit closing date(##.##.####): ");
			printf("Result: %lf\n", sum + GetPercent(sum, from_date, to_date));
			free(from_date);
			free(to_date);
			break;
		}
		case 11:
		case 12:
		{
			system("cls");
			accountNumber = LongChecker("Please, enter account(you will lose all your money in deposit): ");
			account = FindAccount(list->head, accountNumber);
			if (account != NULL)
			{
				passportSeries = StringChecker("Please, enter passport series(you will lose all your money in deposit): ", "QWERTYUIOPLKJHGFDSAZXCVBNM1234567890");
				if (strcmp(account->passortSeries, passportSeries) != 0)
				{
					printf("Invalid passport series\n");
					break;
				}
				if (switchMenu == 4)
				{
					ShowDeposit(account);
					int index = check("Please, enter index: ", 0, account->depSize + 1);
					index--;
					pop(list, passportSeries, index);
				}
				else
				{
					while (pop(list, passportSeries, 0));
				}
				free(passportSeries);
			}
			else
			{
				printf("Invalid account\n");
			}
			break;
		}
		case 13:
		{
			system("cls");
			print(list->head);
			break;
		}
		case 14:
		{
			freeList(list);
			free(list);
			return 0;
		}
		default:
			break;
		}
	}
}

void AddAccount(struct List* list)
{
	char* name = StringChecker("Please, enter name in latin: ", "qwertyuioplkjhgfdsazxcvbnmQWERTYUIOPLKJHGFDSAZXCVBNM");
	char* surname = StringChecker("Please, enter surname in latin: ", "qwertyuioplkjhgfdsazxcvbnmQWERTYUIOPLKJHGFDSAZXCVBNM");
	char* issuingAuthority = StringChecker("Please, enter issuing authority: ", "qwertyuioplkjhgfdsazxcvbnmQWERTYUIOPLKJHGFDSAZXCVBNM");
	char* passportSeries = StringChecker("Please, enter passport series: ", "QWERTYUIOPLKJHGFDSAZXCVBNM1234567890");
	char* timeIn = GetTime("Please, enter date of issue passport(##.##.####): ");
	char* timeExpired = GetTime("Please, enter passport validity(##.##.####): ");
	char* depositCategory = DepositChecker();
	int Balance = check("Please, enter deposit summ: ", -1, 10000);
	push_back(depositCategory, name, surname, issuingAuthority, timeIn, timeExpired, passportSeries, Balance, list);
}
