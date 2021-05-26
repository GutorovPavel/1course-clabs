#include "main.h"
#include <assert.h>
#include <stdio.h>

#define N 80

int TestPalindrom()
{
	char str[N] = "aaaa";
	checker(str);
	assert(Palindrom(str) == 1);
	str[N] = "aaba";
	checker(str);
	assert(Palindrom(str) == 0);
}

#undef main
int main() 
{
	TestPalindrom();
	return 0;
}