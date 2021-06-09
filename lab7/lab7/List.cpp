#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "List.h"
#include "Source.h"

void listCreation(struct List* list)
{
	if (list == NULL)
	{
		printf("No information, list is empty\n");
		return;
	}
	list->size = 0;
	list->head = NULL;
}

void showNode(struct List* list)
{
	if (list == NULL)
	{
		printf("No information, list is empty\n");
		return;
	}
	struct Node* node = list->head;
	for (int i = 0; i < list->size; i++)
	{
		printf("%d: %s %s %lld", i + 1, node->surname, node->name, node->accountNumber);
		node = node->next;
	}
}

struct Deposit* DepositCreation(char* depositCategory, int balance)
{
	struct Deposit* dep = (struct Deposit*)calloc(1, sizeof(struct Deposit));
	dep->depNext = NULL;
	dep->depositCategory = depositCategory;
	dep->balance = balance;
	if (strcmp(depositCategory, "Savings contribution") == 0)
	{
		dep->isLock = 0;
	}
	else if (strcmp(depositCategory, "Cumulative contribution") == 0)
	{
		dep->isLock = 1;
	}
	else
	{
		dep->isLock = 3;
	}
	return dep;
}

struct Node* NodeCreation(char* depositCategory, char* name, char* surname, char* issuingAuthority, char* timeIn, char* timeExpired, char* passportSeries, int balance, struct Node* prev, struct Node* next)
{
	struct Node* node = (struct Node*)calloc(1, sizeof(struct Node));
	node->next = next;
	node->prev = prev;
	node->accountNumber = hashing(passportSeries);
	printf("Account ID: %lld\n", node->accountNumber);
	node->name = name;
	node->surname = surname;
	node->issuingAuthority = issuingAuthority;
	node->timeIn = timeIn;
	node->timeExpired = timeExpired;
	node->passortSeries = passportSeries;
	node->depHead = DepositCreation(depositCategory, balance);
	node->depSize++;
	return node;
}

void ShowDeposit(struct Node* node)
{
	if (node == NULL)
	{
		printf("No information, node is empty\n");
		return;
	}
	struct Deposit* dep = node->depHead;
	for (int i = 0; i < node->depSize; i++)
	{
		printf("%d: %s.\n", i + 1, dep->depositCategory);
		dep = dep->depNext;
	}
}

void AddDeposit_(struct Deposit* dep, char* depositCategory, int balance)
{
	if (dep == NULL)
	{
		printf("No information, deposit is empty\n");
		return;
	}
	struct Deposit* temp = dep;
	while (temp->depNext != NULL)
	{
		temp = temp->depNext;
	}
	temp->depNext = DepositCreation(depositCategory, balance);
}

struct Deposit* findDeposit(struct Node* node, const int index)
{
	if (node == NULL)
	{
		printf("No information, node is empty\n");
		return NULL;
	}
	int count = 0;
	struct Deposit* temp = node->depHead;
	if (index > node->depSize)
	{
		return NULL;
	}
	while (index != count)
	{
		temp = temp->depNext;
		count++;
	}
	return temp;
}

struct Node* FindAccount(struct Node* node, unsigned long long int accountNumber)
{
	if (node == NULL)
	{
		printf("No information, node is empty\n");
		return NULL;
	}
	struct Node* temp = node;
	while (temp->next != NULL)
	{
		if (temp->accountNumber == accountNumber)
		{
			break;
		}
		temp = temp->next;
	}
	if (temp->accountNumber == accountNumber)
	{
		return temp;
	}
	return NULL;
}

void FindSurname(struct Node* node, const char* surname)
{
	if (node == NULL)
	{
		printf("No information, node is empty\n");
		return;
	}
	struct Node* temp = node;
	if (temp == NULL)
	{
		return;
	}
	do
	{
		if (strcmp(temp->surname, surname) == 0)
		{
			printf("%s %s %lld\n", temp->surname, temp->name, temp->accountNumber);
		}
		temp = temp->next;
	} while (temp != NULL);
}

void print(struct Node* node)
{
	if (node == NULL)
	{
		printf("No information, node is empty\n");
		return;
	}
	struct Node* temp = node;
	if (temp == NULL)
	{
		return;
	}
	do
	{
		printf("%s %s %lld\n", temp->surname, temp->name, temp->accountNumber);
		temp = temp->next;
	} while (temp != NULL);
}

struct Node* findDep(struct Node* node, char* passportSeries)
{
	if (node == NULL)
	{
		printf("No information, node is empty\n");
		return NULL;
	}
	struct Node* temp = node;
	while (temp->next != NULL)
	{
		if (temp->passortSeries == passportSeries)
		{
			break;
		}
		temp = temp->next;
	}
	if (temp->passortSeries == passportSeries)
	{
		return temp;
	}
	return NULL;
}

struct Node* AddDeposit(struct Node* node, char* passportSeries, char* depositCategory, int balance)
{
	if (node == NULL)
	{
		printf("No information, node is empty\n");
		return NULL;
	}
	struct Node* temp = node;
	while (temp->next != NULL)
	{
		if (temp->passortSeries == passportSeries)
		{
			break;
		}
		temp = temp->next;
	}
	if (temp->passortSeries == passportSeries)
	{
		AddDeposit_(temp->depHead, depositCategory, balance);
		temp->depSize++;
		return NULL;
	}
	return temp;
}

void push_back(char* depositCategory, char* name, char* surname, char* issuingAuthority, char* timeIn, char* timeExpired, char* passportSeries, int balance, struct List* list)
{
	if (list->head == NULL)
	{
		list->head = NodeCreation(depositCategory, name, surname, issuingAuthority, timeIn, timeExpired, passportSeries, balance, NULL, NULL);
	}
	else
	{
		struct Node* temp = AddDeposit(list->head, passportSeries, depositCategory, balance);
		if (temp == NULL)
		{
			return;
		}
		temp->next = NodeCreation(depositCategory, name, surname, issuingAuthority, timeIn, timeExpired, passportSeries, balance, temp, NULL);
	}
	list->size++;
}

int GetSize(struct List* list)
{
	if (list == NULL)
	{
		printf("No information, list is empty\n");
		return 0;
	}
	return list->size;
}

struct Deposit* pop_dep(struct Node* node, const int index)
{
	if (node == NULL)
	{
		printf("No information, node is empty\n");
		return NULL;
	}
	int counter = 0;
	struct Deposit* temp = node->depHead;
	if (node->depSize < index)
	{
		return node->depHead;
	}
	else if (index == 0)
	{
		node->depHead = node->depHead->depNext;
		free(temp->depositCategory);
		free(temp);
		node->depSize--;
		return node->depHead;
	}
	else
	{
		while (node->depSize != counter)
		{
			if (counter == index - 1)
			{
				break;
			}
			temp = temp->depNext;
			counter++;
		}
		struct Deposit* del = temp->depNext;
		temp = temp->depNext->depNext;
		free(del->depositCategory);
		free(del);
		node->depSize--;
		return node->depHead;
	}
}

void free_pop(struct List* list, struct Node* temp, int index)
{
	temp->depHead = pop_dep(temp, index);
	if (temp->depSize == 0)
	{
		if (temp->next != NULL)
		{
			temp->next->prev = temp->prev;
		}
		if (temp->prev != NULL)
		{
			temp->prev->next = temp->next;
		}
		else
		{
			list->head = temp->next;
		}
		char* txt = toString(temp->accountNumber);
		remove(txt);
		free(txt);
		free(temp->issuingAuthority);
		free(temp->name);
		free(temp->surname);
		free(temp->timeExpired);
		free(temp->timeIn);
		free(temp->passortSeries);
		free(temp);
		list->size--;
		return;
	}
}

int pop(struct List* list, const char* passportSeries, const int index)
{
	if (list == NULL)
	{
		printf("No information, list is empty\n");
		return 0;
	}
	int counter = 0;
	struct Node* temp = list->head;
	while (list->size != counter)
	{
		if (strcmp(temp->passortSeries, passportSeries) == 0)
		{
			break;
		}
		temp = temp->next;
		counter++;
	}
	if (temp == NULL)
	{
		return 0;
	}
	free_pop(list, temp, index);
	printf("Successfull\n");
	return 1;
}

void clear(struct List* list, const char* passportSeries)
{
	if (list == NULL)
	{
		printf("No information, list is empty\n");
		return;
	}
	while (list->size)
	{
		pop(list, passportSeries, 0);
	}
}

struct Node* GetNode(struct List* list, const int index)
{
	if (list == NULL)
	{
		printf("No information, list is empty\n");
		return NULL;
	}
	int counter = 0;
	struct Node* temp = list->head;
	if (index > list->size)
	{
		return NULL;
	}
	while (list->size != counter)
	{
		if (counter == index)
		{
			return temp;
		}
		temp = temp->next;
		counter++;
	}
	return NULL;
}

void sort(struct Node* node)
{
	if (node == NULL)
	{
		printf("No information, node is empty\n");
		return;
	}
	struct Deposit* result = NULL;
	struct Deposit* resultEnd = NULL;
	int size = node->depSize;
	for (int i = 0; i < node->depSize; i++)
	{
		struct Deposit* dep = node->depHead;
		struct Deposit* max = node->depHead;
		for (int j = 0; j < size - 1; j++)
		{
			if (dep->depNext->balance > max->depNext->balance)
			{
				max = dep;
			}
			dep = dep->depNext;
		}
		struct Deposit* temp;
		if (max == node->depHead)
		{
			temp = max;
			node->depHead = max->depNext;
		}
		else
		{
			temp = max->depNext;
			max->depNext = max->depNext->depNext;
		}
		if (result == NULL)
		{
			result = temp;
			resultEnd = result;
		}
		resultEnd->depNext = temp;
		resultEnd = resultEnd->depNext;
		size--;
	}
	node->depHead = result;
	printf("Successfull\n");
	return;
}

void freeList(struct List* list)
{
	if (list == NULL)
	{
		printf("No information, list is empty\n");
		return;
	}
	do
	{
		int counter = 0;
		struct Node* temp = list->head;
		if (temp == NULL)
		{
			return;
		}
		int size = temp->depSize;
		for (int i = 0; i < size; i++)
		{
			free_pop(list, temp, 0);
		}
	} while (list->size);
}